var Statment = require('./statment');


function Connection(conn){
	this.conn_ = conn;
}

module.exports=Connection;

function to_sql(sql,args){

	var re =/\?/; //正则表达式
 	var filter = args.shift();
	while(filter){
		sql=sql.replace(re,"'"+filter+"'");
		filter = args.shift();
	}
	return sql;
}


//callback (err,conn)

//callback (err,statement)
Connection.prototype.query = function(){
	var args = Array.prototype.slice.call(arguments,0);
	var callback = args.pop();
	var sql = args.shift();//sql
	 if (sql.search(/\?/) != -1){
        sql = to_sql(sql,args);
    }
	this.conn_.query(sql,function(err,statment){
		if(err){
			return callback(err,null);
		}else{
			var statment_ = new Statment(statment);
			return callback(null,statment_);
		}
	});
};
//callback (err,null)
Connection.prototype.execute = function(){
	var args = Array.prototype.slice.call(arguments,0);
	var callback = args.pop();
	var sql = args.shift();//sql
	 if (sql.search(/\?/) != -1){
        sql = to_sql(sql,args);
    }
	this.conn_.execute(sql,callback);
};
//return true  or false
Connection.prototype.executesync = function(){
	var args = Array.prototype.slice.call(arguments,0);
	//var callback = args.pop();
	var sql = args.shift();//sql
	if (sql.search(/\?/) != -1){
        sql = to_sql(sql,args);
    }
	//console.log(sql);
	this.conn_.executesync(sql);
};
//return true  or false
Connection.prototype.beginTran = function(){
	this.conn_.begin();
};
//return true  or false
Connection.prototype.commitTran = function(){
	this.conn_.commit();
};
//return true  or false
Connection.prototype.rollbackTran = function(){
	this.conn_.rollback();
};
//return true  or false
Connection.prototype.close = function(){
	this.conn_.close();
};
//return true  or false
Connection.prototype.enterkey = function(key){
	this.conn_.enterkey(key);
};

//return true  or false
Connection.prototype.changekey = function(key){
	this.conn_.changekey(key);
};
//return true  or false
Connection.prototype.delkey = function(){
	this.conn_.delkey();
};

//return true  or false
Connection.prototype.isopen = function(){
	this.conn_.isopen();
};

//return string 
//调用该函数返回最后一次错误，针对同步的API
Connection.prototype.getLastError = function(){
	this.conn_.getLastError();
};



