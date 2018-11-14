
<!-- saved from url=(0030)http://vu.srgb.xyz/README.html -->
<html><head><meta http-equiv="Content-Type" content="text/html; charset=UTF-8"><style type="text/css" abt="234"></style><script>//remove 17173 video ad
doAdblock();
function doAdblock(){
    (function() {
        function A() {}
        A.prototype = {
            rules: {
                '17173_in':{
                    'find':/http:\/\/f\.v\.17173cdn\.com\/(\d+\/)?flash\/PreloaderFile(Customer)?\.swf/,
                    'replace':"http://swf.adtchrome.com/17173_in_20150522.swf"
                },
                '17173_out':{
                    'find':/http:\/\/f\.v\.17173cdn\.com\/(\d+\/)?flash\/PreloaderFileFirstpage\.swf/,
                    'replace':"http://swf.adtchrome.com/17173_out_20150522.swf"
                },
                '17173_live':{
                    'find':/http:\/\/f\.v\.17173cdn\.com\/(\d+\/)?flash\/Player_stream(_firstpage)?\.swf/,
                    'replace':"http://swf.adtchrome.com/17173_stream_20150522.swf"
                },
                '17173_live_out':{
                    'find':/http:\/\/f\.v\.17173cdn\.com\/(\d+\/)?flash\/Player_stream_(custom)?Out\.swf/,
                    'replace':"http://swf.adtchrome.com/17173.out.Live.swf"
                }
            },
            _done: null,
            get done() {
                if(!this._done) {
                    this._done = new Array();
                }
                return this._done;
            },
            addAnimations: function() {
                var style = document.createElement('style');
                style.type = 'text/css';
                style.innerHTML = 'object,embed{\
                -webkit-animation-duration:.001s;-webkit-animation-name:playerInserted;\
                -ms-animation-duration:.001s;-ms-animation-name:playerInserted;\
                -o-animation-duration:.001s;-o-animation-name:playerInserted;\
                animation-duration:.001s;animation-name:playerInserted;}\
                @-webkit-keyframes playerInserted{from{opacity:0.99;}to{opacity:1;}}\
                @-ms-keyframes playerInserted{from{opacity:0.99;}to{opacity:1;}}\
                @-o-keyframes playerInserted{from{opacity:0.99;}to{opacity:1;}}\
                @keyframes playerInserted{from{opacity:0.99;}to{opacity:1;}}';
                document.getElementsByTagName('head')[0].appendChild(style);
            },
            animationsHandler: function(e) {
                if(e.animationName === 'playerInserted') {
                    this.replace(e.target);
                }
            },
            replace: function(elem) {
                if(this.done.indexOf(elem) != -1) return;
                this.done.push(elem);
                var player = elem.data || elem.src;
                if(!player) return;
                var i, find, replace = false;
                for(i in this.rules) {
                    find = this.rules[i]['find'];
                    if(find.test(player)) {
                        replace = this.rules[i]['replace'];
                        if('function' === typeof this.rules[i]['preHandle']) {
                            this.rules[i]['preHandle'].bind(this, elem, find, replace, player)();
                        }else{
                            this.reallyReplace.bind(this, elem, find, replace)();
                        }
                        break;
                    }
                }
            },
            reallyReplace: function(elem, find, replace) {
                elem.data && (elem.data = elem.data.replace(find, replace)) || elem.src && ((elem.src = elem.src.replace(find, replace)) && (elem.style.display = 'block'));
                var b = elem.querySelector("param[name='movie']");
                this.reloadPlugin(elem);
            },
            reloadPlugin: function(elem) {
                var nextSibling = elem.nextSibling;
                var parentNode = elem.parentNode;
                parentNode.removeChild(elem);
                var newElem = elem.cloneNode(true);
                this.done.push(newElem);
                if(nextSibling) {
                    parentNode.insertBefore(newElem, nextSibling);
                } else {
                    parentNode.appendChild(newElem);
                }
            },
            init: function() {
                var handler = this.animationsHandler.bind(this);
                document.body.addEventListener('webkitAnimationStart', handler, false);
                document.body.addEventListener('msAnimationStart', handler, false);
                document.body.addEventListener('oAnimationStart', handler, false);
                document.body.addEventListener('animationstart', handler, false);
                this.addAnimations();
            }
        };
        new A().init();
    })();
}
//remove baidu search ad
if(document.URL.indexOf('www.baidu.com') >= 0){
    if(document && document.getElementsByTagName && document.getElementById && document.body){
        var aa = function(){
            var all = document.body.querySelectorAll("#content_left div,#content_left table");
            for(var i = 0; i < all.length; i++){
                if(/display:\s?(table|block)\s!important/.test(all[i].getAttribute("style"))){all[i].style.display= "none";all[i].style.visibility='hidden';}
            }
            all = document.body.querySelectorAll('.result.c-container[id="1"]');
            //if(all.length == 1) return;
            for(var i = 0; i < all.length; i++){
                if(all[i].innerHTML && all[i].innerHTML.indexOf('广告')>-1){
                    all[i].style.display= "none";all[i].style.visibility='hidden';
                }
            }
        }
        aa();
        document.getElementById('wrapper_wrapper').addEventListener('DOMSubtreeModified',aa)
    };
}
//remove sohu video ad
if (document.URL.indexOf("tv.sohu.com") >= 0){
    if (document.cookie.indexOf("fee_status=true")==-1){document.cookie='fee_status=true'};
}
//remove 56.com video ad
if (document.URL.indexOf("56.com") >= 0){
    if (document.cookie.indexOf("fee_status=true")==-1){document.cookie='fee_status=true'};
}
//fore iqiyi enable html5 player function
if (document.URL.indexOf("iqiyi.com") >= 0){
    if (document.cookie.indexOf("player_forcedType=h5_VOD")==-1){
        document.cookie='player_forcedType=h5_VOD'
        if(localStorage.reloadTime && Date.now() - parseInt(localStorage.reloadTime)<60000){
            console.log('no reload')
        }else{
            location.reload()
            localStorage.reloadTime = Date.now();
        }
    }
}
</script><style type="text/css">object,embed{                -webkit-animation-duration:.001s;-webkit-animation-name:playerInserted;                -ms-animation-duration:.001s;-ms-animation-name:playerInserted;                -o-animation-duration:.001s;-o-animation-name:playerInserted;                animation-duration:.001s;animation-name:playerInserted;}                @-webkit-keyframes playerInserted{from{opacity:0.99;}to{opacity:1;}}                @-ms-keyframes playerInserted{from{opacity:0.99;}to{opacity:1;}}                @-o-keyframes playerInserted{from{opacity:0.99;}to{opacity:1;}}                @keyframes playerInserted{from{opacity:0.99;}to{opacity:1;}}</style></head><body><pre>
rc.local       启动脚本

udp2raw        wg伪装TCP保护服务端

wg_udp2raw.sh  wg 伪装安装脚本 


子目录 wireguard 配置文件
client.conf  客户端配置

key文件四个
cprivatekey
cpublickey
sprivatekey
spublickey  

wg0.conf    wg服务端配置



----   wg_udp2raw.sh----------   

#!/bin/bash                                                                                          

# 停止原先服务                                                                                       
systemctl stop rc-local                                                                              

#安装到启动项 适合debian 9 x64                                                                       

cat &lt;<eof>/etc/rc.local                                                                             
#!/bin/sh -e                                                                                         
#                                                                                                    
# rc.local                                                                                           

udp2raw -s -l0.0.0.0:8855 -r 127.0.0.1:9009 -k "passwd" --raw-mode faketcp  &gt;&gt; /var/log/udp2raw.log &amp;

exit 0                                                                                               
EOF                                                                                                  

chmod +x /etc/rc.local                                                                               
systemctl restart rc-local                                                                           



----------  client.conf  --------                                                                                  
[Interface]                                                                                                                  
# 私匙，自动读取上面刚刚生成的密匙内容                                                                                       
PrivateKey = KMBA1ygggP8wSZRNo0GXek5G1XAm5j3fRcNvXDXZtVQ=                                                                    

# VPN内网IP范围                                                                                                              
Address = 10.0.0.2/24                                                                                                        

# 解析域名用的DNS                                                                                                            
DNS = 8.8.8.8                                                                                                                

# 保持默认                                                                                                                   
MTU = 1300                                                                                                                   

# Wireguard客户端配置文件加入PreUp,Postdown命令调用批处理文件                                                                
PreUp = start   .\route\routes-up.bat                                                                                        
PostDown = start  .\route\routes-down.bat                                                                                    

#### 正常使用Tunsafe点击connect就会调用routes-up.bat将国内IP写进系统路由表，断开disconnect则会调用routes-down.bat删除路由表。
#### 连接成功后可上 http://ip111.cn/ 测试自己的IP。                                                                          

[Peer]                                                                                                                       
# 公匙，自动读取上面刚刚生成的密匙内容                                                                                       
PublicKey = w4q0O90GHpEPxvRf5VBmJKSvh5Ri1r9EwofKNV1+Al8=                                                                     

# 服务器地址和端口，下面的 X.X.X.X 记得更换为你的服务器公网IP，端口根据服务端配置时的监听端口填写                            
Endpoint = 144.202.95.95:9009                                                                                                

# 转发流量的IP范围，下面这个代表所有流量都走VPN                                                                              
AllowedIPs = 0.0.0.0/0, ::0/0                                                                                                

# 保持连接（具体我也不清楚）                                                                                                 
PersistentKeepalive = 25                                                                                                     
</eof></pre></body></html>