#include <ansi.h>

inherit ITEM;

mixed check_title(string arg)
{
    arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);

        if (strlen(filter_color(arg)) > 30 || strlen(arg) > 100)
                return notify_fail("这个外号太长了，为了节约资源，请你重新设定。\n");

    return arg + NOR;
}

void create()
{
        set_name(NOR + YEL "《黄皮手记》" NOR, ({ "huangpi shouji" }) );
        set_weight(100);

        /*if (clonep())
                set_default_object(__FILE__);
        else*/ {
                set("long", YEL "这是一本泛黄的皮册子，里面记载着如何修改您的头衔的秘诀。\n"
                                                "使用后可修改您的头衔（TITLE），指令：retitle 头衔 即可。\n" 
                                                                "下线丢失:否\n" 
                                                        "颜色定义，您可以在您的头衔中加入指定颜色：\n"
                                                                "$BLK$ - 黑色      $NOR$ - 恢复正常颜色\n"
                                                                "$RED$ - 红色      $HIR$ - 亮红色\n"
                                                                "$GRN$ - 绿色      $HIG$ - 亮绿色\n"
                                                                "$YEL$ - 土黄色    $HIY$ - 黄色\n"
                                                                "$BLU$ - 深蓝色    $HIB$ - 蓝色\n"
                                                                "$MAG$ - 浅紫色    $HIM$ - 粉红色\n"
                                                                "$CYN$ - 蓝绿色    $HIC$ - 天青色\n"
                                                                "$WHT$ - 浅灰色    $HIW$ - 白色（或淡紫色）\n\n"
                                                                "根据系统的不同，以上颜色定义有一定偏差。\n" NOR);
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
                add_action("do_retitle", "retitle");
        }
}

int do_retitle(string arg)
{
                object me;

                me = this_player();

                if (! arg)return notify_fail("指令格式: retitle 头衔\n");

        if (! stringp(arg = check_title(arg)))return 1;

                me->set("title", arg);

                me->save();

                write(HIG "修改头衔成功！您现在的江湖称号是：" + arg + "。\n" NOR);

                destruct(this_object());

                return 1;
}

int query_autoload()
{
         return 1;
}