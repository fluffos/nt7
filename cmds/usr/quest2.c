// This program is a part of NT MudLIB
// quest1.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        mapping q;
        string name, npc;

        if( query("ultra_count", me) )
                write(sprintf("南贤交给你的宗师任务，你已经连续完成了 %d 个。\n",
                              query("ultra_count", me)));

        if( !query("ultraquest/npc1", me) )
        {
                write("你现在没有领任何任务！\n");
                return 1;
        }

        if( query("ultraquest/npc5", me) )
        {
                npc=query("ultraquest/npc5", me);
                name=query("ultraquest/name5", me);
        } else
        if( query("ultraquest/npc4", me) )
        {
                npc=query("ultraquest/npc4", me);
                name=query("ultraquest/name4", me);
        } else
        if( query("ultraquest/npc3", me) )
        {
                npc=query("ultraquest/npc3", me);
                name=query("ultraquest/name3", me);
        } else
        if( query("ultraquest/npc2", me) )
        {
                npc=query("ultraquest/npc2", me);
                name=query("ultraquest/name2", me);
        } else
        {
                npc=query("ultraquest/npc1", me);
                name=query("ultraquest/name1", me);
        }

        if( !mapp(q=query("ultraquest/quest", me)) )
        {
                if( query("ultraquest/id", me) )
                {
                        write("你现在的任务是去杀了幕后黑手"+query("ultraquest/name", me)+"("+
                              query("ultraquest/id", me)+")，提他的人头给南贤。\n");
                        return 1;
                }
                write("你现在的任务是去寻找线索知情人" + name + "(" + npc + ")。\n" +
                      "听说他前段日子在"+query("ultraquest/place", me)+"出现过。\n");
                return 1;
        } else
        {
                switch (q["type"])
                {
                case "kill":
                        write(name + "(" + npc + ")吩咐你去割下" HIR +
                              q["name"] + "(" + q["id"] + ")" + NOR "的人头，回来交差。\n");
                        return 1;

                case "give":
                        write(name + "(" + npc + ")吩咐你去把包裹送到" HIR +
                              q["name"] + "(" + q["id"] + ")" + NOR "的手里，回来交差。\n");
                        return 1;

                case "send":
                        write(name + "(" + npc + ")吩咐你去把信送到" HIR +
                              q["name"] + "(" + q["id"] + ")" + NOR "的手里，回来交差。\n");
                        return 1;

                case "guard":
                        write(name + "(" + npc + ")吩咐你留在他那里保护他。\n");
                        return 1;

                case "mathematics":
                        write(name + "(" + npc + ")吩咐你和他比试演算。\n");
                        return 1;

                case "literate":
                        write(name + "(" + npc + ")吩咐你和他比试诗词。\n");
                        return 1;

                case "chess":
                        write(name + "(" + npc + ")吩咐你和他比试棋技。\n");
                        return 1;

                case "calligraphy":
                        write(name + "(" + npc + ")吩咐你帮他写好书法。\n");
                        return 1;

                case "drawing":
                        write(name + "(" + npc + ")吩咐你帮他绘画。\n");
                        return 1;

                case "medical":
                        write(name + "(" + npc + ")吩咐你帮他治病。\n");
                        return 1;
                }
        }

        write("你现在没有领任何任务！\n");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : quest2 显示出你当前的宗师任务。
HELP );
        return 1;
}

