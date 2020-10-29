// This program is a part of NITAN MudLIB 
// redl 2012/12/1 
#include <ansi.h>

inherit NPC;

void create()
{
        set_name(NOR "小丁" NOR, ({ "xiao ding","ding","npc_xiaoding" }) );
        set("title", NOR "通吃帮帮主夫人" NOR);
        set("nickname", MAG "无影狗肉大菜刀" NOR);
        set("gender", "女性");
        set("age", 16);
        set("long", NOR"她就是江湖上赫赫有名的通吃帮寒玲小姐，看起来很是清纯的样子。\n"NOR);
        set("attitude", "peaceful");
        set("str", 25);
        set("con", 25);
        set("int", 25);
        set("dex", 25);
        set("per", 29);

        set("chat_chance", 1);
        set("chat_msg", ({
                                (: command("xixi npc_yangxiaoxie") :),
                                (: command("apple npc_yangxiaoxie") :),
                                (: command("wink npc_yangxiaoxie") :),
        }) );

                set("level", 20);
        set("combat_exp", 10000000);

        set("inquiry", ([
                "小邪"     : "不就在我旁边吗..你都知道了？呃，是的，我吃定他了...\n"+NOR,
        ]));

        setup();

}




