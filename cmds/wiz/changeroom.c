// To change a room's set
// Created by Lonely (06/19/2002)

inherit F_CLEAN_UP;
int do_one_room(object room, string arg, string i);
int main(object me, string arg)
{
        string str;
        string i;

        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! arg || sscanf(arg, "%s %s", str, i) != 2)
                return notify_fail("指令格式：changeroom 属性 值\n");
        do_one_room(environment(me), str, i);
        return 1;
}

int do_one_room(object room, string arg, string i)
{
        string file;
        string old;

        old=query(arg, room);

        reset_eval_cost();
        file = read_file(base_name(room)+".c");
        file = replace_string(file,"        set(\""+arg+"\", "+old+");\n","");
        file = replace_string(file,"        set(\""+arg+"\","+old+");\n","");
        file = replace_string(file,"        set(\""+arg+"\", \""+old+"\");\n","");
        file = replace_string(file,"        set(\""+arg+"\",\""+old+"\");\n","");
        file = replace_string(file,"setup",
        sprintf("set(\"%s\", %s);\n        setup",arg,i));

        if (write_file(base_name(room)+".c",file,1))
                write("Finished room "+ base_name(room) +"\n");
        return 1;
}

int  help(object  me)
{
write(@HELP
指令格式  :  changeroom 属性 值

修改房间属性的指令。

如果房间原本已经有该属性，请确认set("属性",值);之前为Tab
输入的空格，否则先删除原有属性再使用本命令。

使用本命令后必须update here刷新，否则在该房间再次使用时
会造成该房间有两个set("属性",值)，原因不必累述。

如果值是一个字符串则要加上引号，即changeroom 属性 "值"
例如outdoors的属性可以这样使用：

        changeroom outdoors "city"  

就会在房间的setup();上面加一句set("outdoors", "city");
即把房间的outdoors属性改为city。

HELP
        );
        return  1;
}