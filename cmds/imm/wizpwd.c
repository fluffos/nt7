// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// wizpwd.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        
        if (! SECURITY_D->valid_grant(me, "(immortal)")) 
                return 0; 

        if( me != this_player(1) ) return 0;

        ob=query_temp("link_ob", me);
        if( !ob ) return 0;
        while(ob && ob->is_character())ob=query_temp("link_ob", ob);

        write("为了安全起见，请先输入您原来的密码：");
        input_to("get_old_pass", 1, ob);
        return 1;
}

protected void get_old_pass(string pass, object ob)
{
        string old_pass;

        write("\n");
        old_pass=query("wizpwd", ob);
        if( query("wizpwd", ob) )
        {
            if(crypt(pass, old_pass)!=old_pass ) {
                write("密码错误！\n");
                return;
            }
        }
        write("请输入新的密码：");
        input_to("get_new_pass", 1, ob );
}

protected void get_new_pass(string pass, object ob)
{
        write("\n请再输入一次新的密码：");
        input_to("confirm_new_pass", 1, ob, crypt(pass,0));
}

protected void confirm_new_pass(string pass, object ob, string new_pass)
{
        write("\n");
        if( crypt(pass, new_pass)!=new_pass ) {
                write("对不起，您输入的密码并不相同，继续使用原来的密码。\n");
                return;
        }
        seteuid(getuid());
        if( !set("wizpwd",new_pass,ob) ){
                write("密码变更失败！\n");
                return;
        }
         
        set("wizpwd", new_pass, ob);
        ob->save();
        write("密码变更成功。\n");
}

int help(object me)
{
        write(@HELP
指令格式 : passwd
 
这个指令可以修改wiz的第二重密码。
 
HELP
        );
        return 1;
}
