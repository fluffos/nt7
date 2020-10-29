// ----/cmds/usr/allowip.c ----
// allowip.c

#include <ansi.h> 
inherit F_CLEAN_UP;
 
int help();
 
varargs void allow_ip_list(string *allow_ip,string name)
{
    int i;
    if (!name)
        name="你";
    if (allow_ip && sizeof(allow_ip)){
        write("\n"+name+"所设定的登录地址范围有：\n");
        for (i=0;i<sizeof(allow_ip);i++)
                    printf("\t%s\n", allow_ip[i]);
    }else{
        write(YEL+"警告："+name+"目前没有设定任何登录地址，"+name+"的帐号可以从任何地方上线！\n"+NOR);
     if (name=="你")
        help();
    }
}

int vaild_enter(string line,string *allow_ip)
{
    int i;
    string *ip;
    
    if (!sizeof(allow_ip) || !line)  return 1;
    ip=({ line });
    for (i = 0; i < sizeof(allow_ip); i++)
        if (sizeof(regexp(ip, allow_ip[i])) == 1)
            return 1;
    return 0;
}

int main(object me, string arg)
{
    string *allow_ip,line;
    int i;
    string tmp1,tmp2,tmp3,tmp4,term="-s";
    object link_ob;
    
    if (!me || me!=this_player(1))  return 0;
    
    link_ob=query_temp("link_ob", me);
 
    seteuid(ROOT_UID);
 
    allow_ip=query("allow_ip", link_ob);
    if( !arg || arg=="" ) {
        allow_ip_list(allow_ip);
        return 1;
    }
    if (wizardp(me)){
        if (sscanf(arg,"%s %s",term,tmp1)==2){
            link_ob=FINGER_D->acquire_login_ob(tmp1);
            if (link_ob){
                switch(term){
                    case "-p" :
                        allow_ip_list(query("allow_ip", link_ob),query("name", link_ob));
                        return 1;
                    case "-d" :
                        delete("allow_ip", link_ob);
                        write(query("name", link_ob)+"的登录地址设置已被删除。\n");
                        link_ob->save();
                        return 1;
                }
            }
        }
    }

    sscanf(arg, "%s %s", term, arg);
    switch(term){
        case "-?":
             if (!vaild_enter(arg,allow_ip)){
                write(arg+" 不在你所设定的登录地址内。\n");
             }else{
                write(arg+" 可以正常登录。\n");
             }
                return 1;
        case "-d":
            if (!allow_ip || !sizeof(allow_ip))
                return notify_fail(YEL+"\n警告：你目前没有设定任何登录地址，你的帐号可以从任何地方上线！\n"+NOR);
            if (member_array(arg,allow_ip)==-1)    return notify_fail("你并没有设定"+arg+"\n");
            allow_ip -= ({ arg });
                line=query_ip_number(me);
            if (!vaild_enter(line,allow_ip)){
                write("警告：你目前的IP地址 "+line+" 不在你所设定的登录地址内。\n请重新设置！\n");
                return 1;
            }
            break;
        case "-s" :
            allow_ip=explode(arg,"|");
            allow_ip -= ({""});
            write("设定登录地址：");
            for (i=0;i<sizeof(allow_ip);i++){
                if (sscanf(allow_ip[i],"%s.%s.%s.%s",tmp1,tmp2,tmp3,tmp4)==4){
                    if (tmp1=="*")
                        allow_ip -= ({ allow_ip[i] });
                    else
                        write(" "+allow_ip[i]);
              }else  return help();
            }
            line=query_ip_number(me);
            if (!vaild_enter(line,allow_ip)){
                   write(YEL+"\n警告：你目前的IP地址 "+line+" 不在你所设定的登录地址内。\n请重新设置！\n"+NOR);
                    return 1;
            }else{
                break;
            }
            return 1;
       default:
            return help();
    }
    write("\nOK!\n");
        
        if( link_ob=query_temp("link_ob", me) )
                set("allow_ip", allow_ip, link_ob);
        
        link_ob->save();
    return 1;
}
 
int help()
{
        write(@TEXT
指令格式：allowip [-?] [-d] [IP地址或范围]
 
设定自己的登录IP地址，如
      allowip 202.96.138.138

也可设定一个IP地址范围，如
      allowip 202.96.138.*

也可同时设定多个地址范围(不超过五个)，中间用"|"隔开，如
      allowip 202.96.138.138|202.98.100.*|172.21.*.*

即使别人知道你的密码，也不能从其他ip地址登录。

其他参数:

-?  : 验证某个IP地址是否能登录
-d  : 删除某个登录地址

TEXT
        );
        return 1;
}
