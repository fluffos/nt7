// This program is a part of NITAN MudLIB 
// redl 2013/8

#include <ansi.h>
inherit NPC;

void create()
{
        set_name(NOR "殷叶" NOR, ({ "ying ye", "ying" }));
                set("nickname", CYN "清洁大妈" NOR);
        set("long", @LONG
这是一个在学校里扫地的大妈，牙尖嘴利，口味颇重。
LONG);
        set("gender", "男性" );
        set("age", 36);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 50000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 50000);
        set("neili", 50000);
        set("jiali", 350);
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("per", 13);
        set("combat_exp", 1333000);

        set("inquiry", ([
                "入学" : "问我一个扫地的干嘛？你到教室里直接付钱给老师就行。\n"+NOR,
                "注音" : "对，何止我的姓是错的注音，我整个姓名都是猥琐的谐音。\n"+NOR,
        ]));

        setup();
        carry_object("/clone/misc/cloth")->wear();

}




