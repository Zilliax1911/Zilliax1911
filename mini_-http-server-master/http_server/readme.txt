
此为说明文档
一、自主服务器实现的功能：
1.在线计算器（test_cgi）
2.注册信息提交到 MySQL数据库（mysql_cgi，有bug）
3.返回静态网页（比如/contact.html、/about.html）
4.返回错误网页（/404.html）
5.表单上传数据（默认的index.html，会返回一个表单数据，最后用户提交数据跳转到CGI子程序-》在线计算器）


二、使用方法：
执行./build.sh可执行程序生成output目录
output目录为发布版本，包括httpserver可执行程序和wwwroot根目录
服务器端使用方法：
执行./httpserver可执行程序，用于启动该服务器；
wwwroot根目录里面保存着服务器提供给用户的资源；

用户使用方法：采用url访问服务器资源
url标准格式：protocol :// hostname[:port] / path / [:parameters][?query]#fragment
比如：http://43.142.92.23:8081/a/b/c.file?a=100&b=200
url里面的资源路径一般不是从服务器主机的根目录开始的，是虚拟路径，从wwwroot路径开始的
若url中没有指明资源路径，一般服务器会默认返回首页index.html


三、注意事项：
（1）cgi目录里面提供的是cgi机制需要用到的子程序，比如：
test_cgi可执行程序（实现的是在线计算器）
shell_cgi.sh可执行程序（返回静态网页）
python_cgi.py可执行程序（返回静态网页）
mysql_cgi可执行程序（实现的是注册信息提交到数据库，有bug待调试）

最终的发布版本会将各个可执行程序拷贝到output目录下wwwroot目录下去
通过浏览器访问时候，若url里面指明了访问的资源是这些可执行程序
则后台服务器会调用CGI机制，执行相应的子程序，处理数据

（2）表单相关说明：
返回的表单一般是让用户上传数据的
返回的表单里面规定了用户上传数据时是用GET方法还是POST方法；