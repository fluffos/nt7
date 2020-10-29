//tranemote.c
//Made by jason@pkuxkx
//FreeWare
#define ERROR "指令格式：tranemote emote 来源emote文件\n"
inherit F_SAVE;
string source_file="";
mapping emote=([]);
string query_save_file()
{
        return source_file;
}
int main(object me,string arg)
{
        mapping old_emote=([]);
        string ee,file,*key,*key2;

           if (! SECURITY_D->valid_grant(me, "(admin)")) 
              return 0; 
        if(!arg||arg=="")
                return notify_fail(ERROR);
        if(sscanf(arg,"%s %s",ee,file)!=2)
        {
                return notify_fail(ERROR);
        }
        if(file_size(file+".o")<=0)
                return notify_fail("读emote源文件错误。\n" );
        source_file=file;
        if(!restore())
        {
                return notify_fail("emote源文件无法Restore。\n");
        }
        old_emote=emote;
        if(!mapp(old_emote)||sizeof(old_emote)<=0)
        {
                return notify_fail("emote源文件无法Restore。\n");
        }
        source_file="/data/emoted";
        if(!restore())
        {
                return notify_fail("emote目标文件错误。\n");
        }
        if(!mapp(emote)||sizeof(emote)<=0)
        {
                return notify_fail("emote目标文件无法Restore。\n");
        }
        key=keys(old_emote);
        if(wizardp(me)&&wizhood(me)=="(admin)")
        {
                int unit=0;
                string nowtime;
                if(ee=="-All")
                {
                        nowtime=""+time();
                        cp("/data/emoted.o","/data/emoted.o."+nowtime);
                        key2=keys(emote);
                        shout("Emote 文件转换中。。。。\n");
                        for(int i=0;i < sizeof(key);i++)
                        {
                                reset_eval_cost();
                                if(member_array(key[i],key2)!=-1) continue;
                                if(!mapp(old_emote[key[i]])) continue;
                                EMOTE_D->set_emote(key[i],old_emote[key[i]]);
                                write(key[i]+"\n");
                                unit++;
                        }
                        write("Emote 文件 "+file+" 转换进入/data/emoted.o成功！\
n");            
                        write("一共有"+chinese_number(unit)+"个emote转换成功。\n
");
                        write("现有emote备份为"+"/data/emoted.o."+nowtime+"\n");
                        log_file("tran_emote",getuid(me)+"转换 "+file+" 中的Emot
e进入当前Emote中。
\n"+
                        "时间："+ctime(time())+"\n"+
                        "现有emote备份为"+"/data/emoted.o."+nowtime+"\n");
                        return 1;
                }
        
        }
        ee=lower_case(ee);
        if(member_array(ee,key)==-1)
        {
                return notify_fail(ee+" 不存在于 "+file+"。\n");
        }
        if(!mapp(old_emote[ee]))
        {
                return notify_fail(ee+" 不是一个合法的emote。\n");
        }
        if(!undefinedp(emote[ee]))
        {
                return notify_fail(ee+" 存在于目标emote文件中，不能覆盖。\n");
        }
        EMOTE_D->set_emote(ee,old_emote[ee]);
        write("Emote转换 "+ee+" 成功。\n");
        return 1;
}
int help(object me)
{
        write(@HELP
指令格式：tranemote emote 来源emote文件
将来源emote文件中的指定emote加入当前emote文件中。
格式二：tranemote -All 来源emote文件
将来源emote文件中所有当前emote文件中没有的emote加入。
同时给当前emote文件按时间备份。
HELP
        );
        return 1;
}
