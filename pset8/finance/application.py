import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():

    queries = db.execute("SELECT symbol, sum(shares) FROM purchases WHERE user_id = :id GROUP BY symbol HAVING sum(shares)>0",
                id=session["user_id"])

    values=[]

    for query in queries:
        symbol = query['symbol']
        shares = query['sum(shares)']

        lookup_symbol = lookup(symbol)
        name = lookup_symbol["name"]
        price = lookup_symbol["price"]

        total = round(price*shares,2)

        value = []

        value.append(symbol)
        value.append(shares)
        value.append(name)
        value.append(price)
        value.append(total)

        values.append(value)

    cash = db.execute("SELECT cash FROM users WHERE id = :id",
                          id=session["user_id"])
    cash = round(cash[0]['cash'], 2)

    total_shares = 0
    for value in values:
        total_shares += value[4]

    total = round(total_shares + cash, 2)
    # print("total", total)
    # print("total_shares", total_shares)
    # print(values)

    return render_template("index.html", values = values, cash = cash, total = total)

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        lookup_symbol=lookup(request.form.get("symbol"))
        price=lookup_symbol["price"]
        amount=int(request.form.get("shares"))
        # print("price", type(price), price)
        # print("amount", type(amount), amount)
        order=price*amount
        available = db.execute("SELECT cash FROM users WHERE id = :id",
                          id=session["user_id"])
        if len(available) != 1:
            return apology("list namiesto 1 hodnoty", 403)
        print("available", type(available), available)
        if available[0]['cash'] < order:
            return apology("Not enough moneys", 403)
        else:
            time = db.execute("SELECT CURRENT_TIMESTAMP")
            print("time", time)
            db.execute("UPDATE users SET cash = :cash WHERE id=:id",
                        cash= available[0]['cash']-order, id=session["user_id"])
            db.execute("INSERT INTO purchases (user_id, symbol, shares, price, time) VALUES (?,?,?,?,?)",
                        session["user_id"], request.form.get("symbol").upper(), amount, price, time[0]['CURRENT_TIMESTAMP'])
            return redirect("/")
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    rows = db.execute("SELECT symbol, shares, price, time FROM purchases WHERE user_id = :id",
                id=session["user_id"])

    values=[]

    for row in rows:
        symbol = row['symbol']
        shares = row['shares']
        price = round(row['price'],2)
        time = row['time']

        value=[symbol, shares, price, time]

        values.append(value)
        
    print("values", values)

    return render_template("history.html", values=values)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        lookup_symbol123=lookup(request.form.get("symbol"))
        if lookup_symbol123 == None:
            np = None
        elif isinstance(lookup_symbol123,dict):
            np = "dict"

        return render_template("quote.stonk.html", lookup_symbol=lookup_symbol123 , np=np )
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # insert user into users table

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username when registering", 403)
        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)
        elif request.form.get("password") != request.form.get("password-2"):
            return apology("Password don't match, voe!", 403)


        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) > 0:
            return apology("Username already taken, biatch!", 403)


        db.execute("INSERT INTO users (username, hash) VALUES (:username, :password_hash)",
                      username=request.form.get("username"),
                      password_hash=generate_password_hash(request.form.get("password"))
                  )

        # Login user after registration

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1:
            return apology("Reg failed, sorry!", 403)


        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")


    elif request.method == "GET":
        # display registration form
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        lookup_symbol=lookup(request.form.get("symbol"))
        symbol=lookup_symbol["symbol"]
        price=lookup_symbol["price"]
        amount=int(request.form.get("shares"))
        order=price*amount
        print("symbol", symbol )

        query = db.execute("SELECT symbol, sum(shares) FROM purchases WHERE user_id = :id AND symbol = :symbol GROUP BY symbol HAVING sum(shares)>0",
            id=session["user_id"], symbol = symbol )
        available = db.execute("SELECT cash FROM users WHERE id = :id",
                          id=session["user_id"])

        print("query", query)

        if amount > query[0]['sum(shares)']:
            return apology("Don't have enough", 403)
        else:
            time = db.execute("SELECT CURRENT_TIMESTAMP")
            db.execute("UPDATE users SET cash = :cash WHERE id=:id",
                cash= available[0]['cash']+order, id=session["user_id"])
            db.execute("INSERT INTO purchases (user_id, symbol, shares, price, time) VALUES (?,?,?,?,?)",
                        session["user_id"], request.form.get("symbol").upper(), 0-amount, price, time[0]['CURRENT_TIMESTAMP'])


        return redirect("/")
    else:
        queries = db.execute("SELECT symbol, sum(shares) FROM purchases WHERE user_id = :id GROUP BY symbol HAVING sum(shares)>0",
            id=session["user_id"])

        stocks = map(lambda query: query['symbol'], queries)
        # stocks = list(stocks)
        return render_template("sell.html", stocks=stocks)



def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
