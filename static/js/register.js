const inputID=document.getElementById('inputID1');
const inputEmail=document.getElementById('inputE-mail2');
const inputPassword=document.getElementById('inputPassword2');
let legal;
let legal_ID;
let legal_Email;
let legal_Password;
let cnt;
var recIDError=new Array(21);

// 验证ID规范
function judgeID(){
	cnt=0;
	let ID=inputID.value;
	for(let i=0;i<ID.length;i++){
		if(!((ID[i]>='A'&&ID[i]<='Z')||(ID[i]>='a'&&ID[i]<='z')||(ID[i]=='_')||(ID[i]>='0'&&ID[i]<='9'))){
			legal_ID=false;
			recIDError[cnt]=ID[i];
			cnt++;
		}
	}
	if(ID.length==0)cnt=-1;
}

// 验证密码规范
function judgePassword(){
	let _password=inputPassword.value;
	if(_password==null||_password==='')legal_Password=false;
}

// 验证邮箱规范
function judgeEmail(){
	let email=inputEmail.value;
	if(!email.match(/^\w+@\w+\.\w+$/i))legal_Email=false;
}

// 开始验证
function judge(){
	legal=false;
	legal_ID=true;
	legal_Email=true;
	legal_Password=true;
	judgeID();
	judgePassword();
	judgeEmail();
	if(legal_ID&&legal_Email&&legal_Password)legal=true;
	if(legal){
		// 连接数据库等等
	}
	else{
		// 回弹错误信息
		let Error="";
		if(cnt==-1)Error+="ID should not be blank.\n";
		else
		if(!legal_ID){
			Error+="These characters are illegal in ID:\n";
			for(let i=0;i<cnt-1;i++){
				Error+=recIDError[i];
			}
			Error+=recIDError[cnt-1];
			Error+=".\n";
		}
		if(!legal_Email){
			Error+="Your email is illegal or blank.\n";
		}
		if(!legal_Password){
			Error+="Password should not be blank.\n";
		}
		alert(Error);
	}
}
// 控制按钮事件绑定
registerConfirm.addEventListener('click', judge);
