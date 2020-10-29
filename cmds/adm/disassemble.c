// disassemble.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string target, file, f;
        object ob;

        if( this_player(1) != me )
                return notify_fail("你没有这个权力。\n");

        if( !SECURITY_D->valid_grant(me, "(admin)") )
                return 0;

        seteuid(geteuid(me));

        if( !arg || sscanf(arg, "%s %s", target, file) != 2 )
                return notify_fail("指令格式：disassemble <物件> <输出档名>\n");

        if( !ob ) ob = present(target, me);
        if( !ob ) ob = present(target, environment(me));
        if( !ob ) {
                f=resolve_path(query("cwd", me),target);
                if( file_size(f + ".c") > 0 ) {
                        f->foo();
                        ob = find_object(f);
                }
        }

        if( !ob ) return notify_fail("你要反组译哪一个物件？\n");

        f=resolve_path(query("cwd", me),file);
        write("反组译输出至 " + f + "　\n");
        dump_prog(ob, 3, f);
        write("Ok.\n");

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : 指令格式：disassemble <物件> <输出档名>

将一个物件的反编译码输出至指定的档案。你应当有这个
档案的写权限。

HELP
    );
    return 1;
}