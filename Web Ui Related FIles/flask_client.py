import json
import socket
import secrets
from forms import ApplyForm, LoginForm, RegistrationForm, FindLoanDataForm
from flask_client_header import disconnect_from_server, send_data_to_server
from flask import Flask, render_template, request, flash, redirect, url_for, session

HEADER = 64
PORT = 5050
SERVER = socket.gethostbyname(socket.gethostname())
ADDR = (SERVER, PORT)
DISCONNECT_MESSAGE = "!!!DISCONNECT"
FORMAT = 'utf-8'


app = Flask(__name__)

app.config['SECRET_KEY'] = secrets.token_bytes(16) 


@app.route("/")
@app.route("/home")
def home():

    return render_template('home.html')


@app.route("/apply_for_loan", methods=['GET', 'POST'])
def apply_for_loan():
    menu_response = 1
    form = ApplyForm()

    if form.validate_on_submit():
        client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client.connect(ADDR)
        
        user_name = form.username.data
        user_credit_score = form.user_credit_score.data
        user_monthly_income = form.user_monthly_income.data
        user_financial_reserves = form.user_financial_reserves.data
        user_debt_to_income_percentage = form.user_debt_to_income_ratio.data
        user_loan_amoumnt_requested = form.user_loan_amoumnt_requested.data
        user_loan_duration = form.user_loan_duration.data
        
        customer_data = {
            "user_name" : user_name,
            "user_credit_score" : user_credit_score,
            "user_monthly_income" : user_monthly_income,
            "user_financial_reserves" : user_financial_reserves,
            "user_debt_to_income_ratio" : user_debt_to_income_percentage / 100,
            "user_loan_amoumnt_requested" : user_loan_amoumnt_requested,
            "user_loan_duration" : user_loan_duration,
            "user_loan_id" : None,
            "user_has_loan_id" : None
        }
        
        instructions = {
            "menu_response" : menu_response,
            "dev_menu_response" : None,
            "search_menu_response" : None,
            "generate_data_for_db" : False,
            "num_data_to_generate" : None,
            "perform_data_analysis_on_all_generated_csv_data" : False,
            "store_all_db_data_for_external_analysis" : False
        }
        
        data_to_send = {
            "customer_data" : customer_data,
            "instructions" : instructions
        }
        
        json_data = json.dumps(data_to_send, indent = 2)
        print(json_data)
        
        operation_state, retrieved_user_data, list_of_retrieved_user_data = send_data_to_server(json_data, client)
        
        disconnect_from_server(client)
        
        if  (operation_state["added_user_data_successfully"] == True):
            session['customer_data'] = customer_data
            return redirect(url_for("display_loan_data"))
        
    return render_template('apply_for_loan.html', form = form, title = 'apply_for_loan')


@app.route("/display_loan_data", methods = ['GET', 'POST'])
def display_loan_data():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(ADDR)
        
    menu_response = 2
    customer_data = session.get('customer_data')
    
    instructions = {
        "menu_response" : menu_response,
        "dev_menu_response" : None,
        "search_menu_response" : None,
        "generate_data_for_db" : False,
        "num_data_to_generate" : None,
        "perform_data_analysis_on_all_generated_csv_data" : False,
        "store_all_db_data_for_external_analysis" : False
    }
    
    data_to_send = {
        "customer_data" : customer_data,
        "instructions" : instructions
    }
    
    json_data = json.dumps(data_to_send, indent = 2)
    print(json_data)
    
    operation_state, retrieved_user_data, list_of_retrieved_user_data = send_data_to_server(json_data, client)
    
    disconnect_from_server(client)
    
    return render_template('display_loan_data.html', list_of_retrieved_user_data = list_of_retrieved_user_data, title = 'display_loan_data')
    

@app.route("/bank_with_us", methods=['GET', 'POST'])
def bank_with_us():
    return "<h1> Coming soon</h1>"


@app.route("/register", methods = ['GET', 'POST'])
def register():
    form = RegistrationForm()
    if form.validate_on_submit():
        flash(f' Account created for {form.username.data}!', 'success')
        return redirect(url_for('home'))
    
    return render_template('register.html', title = 'Register', form = form)


@app.route("/login", methods = ['GET', 'POST'])
def login():
    form = LoginForm()
    if form.validate_on_submit():
        if form.email.data == 'admin@test.com' and form.password.data == 'password':
            flash('You have been logged in!', 'success')
            return redirect(url_for('home'))
        else:
            flash('Login Unsuccessful. Please check username and password', 'danger')
    return render_template('login.html', title = 'Login', form = form)


@app.route("/find_loan_details", methods = ['GET', 'POST'])
def find_loan_details():
    menu_response = 2
    form = FindLoanDataForm()
    
    if form.validate_on_submit():
        flash(f' Loan data for {form.username.data}', 'success')
        
        user_name = form.username.data
        
        customer_data = {
            "user_name" : user_name,
            "user_credit_score" : None,
            "user_monthly_income" : None,
            "user_financial_reserves" : None,
            "user_debt_to_income_ratio" : None,
            "user_loan_amoumnt_requested" : None,
            "user_loan_duration" : None,
            "user_loan_id" : None,
            "user_has_loan_id" : False
        }
        
        instructions = {
            "menu_response" : menu_response,
            "dev_menu_response" : None,
            "search_menu_response" : None,
            "generate_data_for_db" : False,
            "num_data_to_generate" : None,
            "perform_data_analysis_on_all_generated_csv_data" : False,
            "store_all_db_data_for_external_analysis" : False
        }
        
        data_to_send = {
            "customer_data" : customer_data,
            "instructions" : instructions
        }
        
        json_data = json.dumps(data_to_send, indent = 2)
        
        print(json_data)
        session['customer_data'] = customer_data

        return redirect(url_for("display_loan_data"))
    
    return render_template('find_loan_details.html', form = form, title = 'find_loan_details')


@app.route("/test_canva", methods=['GET', 'POST'])
def test_canva():
    return redirect("https://test-canva-with-flask32.my.canva.site/")    


if __name__ == '__main__':
    # app.run(debug = True)
    app.run(host='0.0.0.0', port=5000, debug = True)