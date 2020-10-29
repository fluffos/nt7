#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "《百家姓》" NOR, ({ "baijia xing" }) );
        set_weight(100);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", HIW "这是一本《百家姓》册子，里面记载着各种姓氏及起源。\n"
                                                "使用后可修改您的姓名，指令：rename 姓 名 即可。\n" 
                                                                "下线丢失:否\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                        set("unit", "本");
        }

        setup();
}

void init()
{
        if (this_player() == environment())
        {
                add_action("do_rename", "rename");
        }
}

int do_rename(string arg)
{
                object me;
                string surname, purename, new_name;
                string result;

                me = this_player();

                if (! arg)return notify_fail("指令格式: rename 姓 名\n");

                if (sscanf(arg, "%s %s", surname, purename) != 2)
                                return notify_fail("指令格式: rename 姓 名\n");

                new_name = surname + purename;

                if (! LOGIN_D->check_legal_name(new_name, 8))return 1;

                result = NAME_D->change_name(me, new_name);

                if (result)
                {
                                write(result + "\n");
                                return 1;
                }
                else
                {        
                        write(HIG "修改姓名成功!\n" NOR);
                        me->set("surname", surname);
                        me->set("purename", purename);
                }
                me->save();

                destruct(this_object());

                return 1;
}

int query_autoload()
{
         return 1;
}