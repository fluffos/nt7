//edit by smallfish 1998.07.16
// Smallfish@Huaxia

#include <ansi.h>
inherit F_CLEAN_UP;

int count3=0;
int if3();
int main(object me,string arg)
{
        object tempob,user_ob;
        string func,tilde,type;
        int val1,val2,i,j,ppl_cnt;
        string *dir, *ppls;
        string tempid, tempname;
        mixed info;
        int info2,online;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (!arg)
                return notify_fail("你要查什么？\n");
        sscanf(arg,"%s %s %s %d %d",type,func,tilde,val1,val2);
        if (!type && type != "skill" && type != "setting")
                return notify_fail("参数错误！请用help searchuser!\n");
        if ((!tilde)||((tilde!=">")&&(tilde!="<")&&(tilde!="=")&&(tilde!="<>")))
                return notify_fail("匹配符错误！请用help searchuser!\n");
        if (!val1)
                return notify_fail("缺少第一参数！请用help searchuser!\n");
        if ((!val2)&&(tilde=="<>"))
                return notify_fail("缺少第二参数!请用help searchuser!\n");
        if ((val2<=val1)&&(tilde=="<>"))
                return notify_fail("第一、第二参数配置错误!请用help searchuser!\n");
        message("system", "\n*** 正在检查玩家储存档参数，这可能要几分钟时间，请稍候.... ***\n", users());

        seteuid(getuid());
        write("检查中：\n");
        log_file("static/check_log", sprintf("-------------------------------------------------\n"));
        log_file("static/check_log", sprintf("符合条件：[%s]%s%s%d,%d的玩家清单：\n",type,func,tilde,val1,val2));
        count3=0;
        ppl_cnt = 0;
        dir = get_dir(DATA_DIR + "login/");
        for(i=0; i<sizeof(dir); i++) {
                reset_eval_cost();
                write(dir[i]);
                ppls = get_dir(DATA_DIR + "login/" + dir[i] + "/",-1);
                     ppl_cnt += sizeof(ppls);
                for(j=0; j<sizeof(ppls); j++) {
                        if( sscanf(ppls[j][0], "%s.o",tempid)==1 )
                     {
                                tempob=new(LOGIN_OB);
                                set("id", tempid, tempob);

                                if(!tempob->restore())
                           {
                                   destruct(tempob);
                                         write("没有" + tempid + "这个玩家!\n");
                                   continue;
                           }

                           if( query("id", tempob) != tempid )
                           {
                                   destruct(tempob);
                                   write("玩家"+tempid+"的ID"+query("id", tempob)+"不正确。\n");
                                   continue;
                           }

                           if (! objectp(user_ob = find_player(tempid)))
                           {
                                   online = 0;//该玩家不在线
                                   user_ob = LOGIN_D->make_body(tempob);
                                   if (! user_ob)
                                   {
                                           destruct(tempob);
                                           write("无法生成玩家"+tempid+"。\n");
                                           continue;
                                   }

                                   if (! user_ob->restore())
                                   {
                                           destruct(tempob);
                                           destruct(user_ob);
                                           write("无法读取玩家档案"+tempid+"。\n");
                                           continue;
                                   }
                           } else
                                   online = 1;

                           destruct(tempob);

                           tempid=query("id", user_ob);
                           tempname = user_ob->name(1);

                           if (type=="skill"){
                           if (user_ob->query_skill(func,1))
                           switch (tilde) {
                           case ">":  
                                  if (user_ob->query_skill(func,1)>val1){
                                        log_file("static/check_log",sprintf("%s[%s] %s:%d | ",tempid,tempname,func,user_ob->query_skill(func)));
                                  if3();
                                        }
                                        break;
                           case "<":
                                  if (user_ob->query_skill(func)<val1) {
                                        log_file("static/check_log",sprintf("%s[%s] %s:%d | ",tempid,tempname,func,user_ob->query_skill(func)));
                                        if3();
                                        }
                                        break;
                           case "=":
                                  if (user_ob->query_skill(func)==val1){
                                        log_file("static/check_log",sprintf("%s[%s] %s:%d | ",tempid,tempname,func,user_ob->query_skill(func)));
                                        if3();
                                        }
                                        break;
                                case "<>":
                                  if ((user_ob->query_skill(func)>val1) && (user_ob->query_skill(func)<val2)) {
                                        log_file("static/check_log",sprintf("%s[%s] %s:%d | ",tempid,tempname,func,user_ob->query_skill(func)));
                                        if3();
                                        }
                                        break;
                                }//switch
                                }//if (type=="skill")
                                else{
                           if( query(func, user_ob) )
                           switch (tilde) {
                           case ">":  
                                  if( query(func, user_ob)>val1){
                                        log_file("static/check_log",sprintf("%s[%s]%s:%d|",tempid,tempname,func,query(func, user_ob)));
                                  if3();
                                        }
                                        break;
                           case "<":
                                  if( query(func, user_ob)<val1){
                                        log_file("static/check_log",sprintf("%s[%s]%s:%d|",tempid,tempname,func,query(func, user_ob)));
                                        if3();
                                        }
                                        break;
                           case "=":
                                  if( query(func, user_ob) == val1){
                                        log_file("static/check_log",sprintf("%s[%s]%s:%d|",tempid,tempname,func,query(func, user_ob)));
                                        if3();
                                        }
                                        break;
                                case "<>":
                                  if( (query(func, user_ob)>val1) && (query(func, user_ob)<val2)){
                                        log_file("static/check_log",sprintf("%s[%s]%s:%d|",tempid,tempname,func,query(func, user_ob)));
                                        if3();
                                        }
                                        break;
                                }//switch
                                }//else
                           if (!online) destruct(user_ob);
                      }//if( sscanf(ppls[j][0], "%s.o",tempid)==1 )
                }//for(j=0; j<sizeof(ppls); j++) {
        }//for(i=0; i<sizeof(dir); i++) {
        
        write("\n\n总共有"+ ppl_cnt + "位使用者。\n");
        write( count3 + " 个使用者符合检查要求。\n");
        log_file("static/check_log",sprintf("\n此次检查由%s[%s]在%s操作!\n",query("name", this_player()),geteuid(this_player()),ctime(time())[0..15]));
        return 1;
}//main

int if3()
{
       log_file("static/check_log",sprintf("\n"));
       count3++;
       return 1;
}

int help(object me)
{
        write(@HELP
指令格式: searchuser <skill|setting> <参数> <表达符号> <数值1> [数值2]
检查MUD中所有在线未在线玩家中，符合指定条件的玩家信息，记录
存放在/log/static/check_log目录下。
其中skill表示检查玩家的武功，setting表示检查玩家的其它各类
属性。
表达符号有：
>    大于符号
<    小于符号
=    等于符号
<>   区段，表示在数值1和数值2之间

HELP );
        return 1;
}