// Code of HuaXia
// roomlong.c
// Smallfish@Huaxia


inherit F_CLEAN_UP;

int help(object me);
int is_room(object ob);

int main(object me, string arg)
{
        int i,begin1,begin2;
        string *filetext;
        string *temptext;
        object ob;
        string file,long;
        string str1,str2,tempstr,tempstr1;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        seteuid(geteuid(me));

        if (! arg) return notify_fail("指令格式 : roomlong <房间档名>|here \n");

        file=resolve_path(query("cwd", me),arg);


        if (file_size(file) < 0)

        {

                ob = present(arg, me);

                if (! ob) ob = present(arg, environment(me));

                if (! ob) return notify_fail("没有这个档案1。\n");

                file = base_name(ob) + ".c";

        }


        if (! SECURITY_D->valid_read(file, me, "write"))

                return notify_fail("没有这个档案2。\n");


        ob = load_object(file);
        if (!ob) return notify_fail(file + "这个档案有错误！\n");

        if (!is_room(ob))
                return notify_fail("这不是一个房间档案。\n");

        long=replace_string(query("long", ob),"\n","");
        long = replace_string(long,"“","『");
        long = replace_string(long,"”","』");

        if (clonep(ob) && !userp(ob)) destruct(ob);

        filetext = explode(read_file(file), "\n");

        temptext = explode(sort_string(long,70,4)+"\n","\n");
        temptext -= ({ "" });

        begin1 = 0;
        begin2 = 0;
        for (i = 0;i < sizeof(filetext);i ++)
        {
                tempstr = "";
                tempstr1 = "";

                tempstr = replace_string(filetext[i]," ","");
                tempstr = replace_string(tempstr,"\t","");
                if (i != sizeof(filetext) -1)
                {
                        tempstr1 = replace_string(filetext[i+1]," ","");
                        tempstr1 = replace_string(tempstr1,"\t","");
                }
                if (tempstr == "set\(\"long\",@LONG")
                {
                        begin1 = i;
                }
                if (tempstr == "LONG\);")
                {
                        begin2 = i;
                        break;
                } else
                if (tempstr == "LONG" && tempstr1 = "\);")
                {
                        begin2 = i+1;
                        break;
                }
        }

        if (!begin1)
                return notify_fail("没有定位成功描述行首！\n");

        if (!begin2)
                return notify_fail("没有定位成功描述行尾！\n");

        str1 = "        set\(\"long\", @LONG\n";
        str2 = "LONG \);\n";
        rm(file);

        for (i = 0;i < begin1;i ++)
                write_file(file,filetext[i]+"\n",0);

        write_file(file,str1,0);
        
        for (i = 0;i < sizeof(temptext);i ++)
                write_file(file,temptext[i]+"\n",0);

        write_file(file,str2,0);

        for (i = begin2+1;i < sizeof(filetext);i ++)
                write_file(file,filetext[i]+"\n",0);

        write("ok.\n");
        return 1;
}

int is_room(object ob)
{
        string file,filetext;

        if (inherits(ROOM,ob)) return 1;
        if( !stringp(query("long", ob)))return 0;
        file = base_name(ob) + ".c";
        if (file_size(file) < 0) return 0;
        filetext = read_file(file);
        if (strsrch(filetext,"inherit ROOM;") == -1) return 0;
        return 1;
}

int help(object me)
{
write(@HELP
指令格式 : roomlong <房间档案>|here

此指令可让将房间的描述格式化为七十个字符长度。
HELP
    );
    return 1;
}