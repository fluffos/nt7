#include <ansi.h>

inherit NPC;

int move_bhd();

void create()
{
        set_name(HIM "谢晓词" NOR, ({ "xiexiao ci", "xiexiao", "ci" }));
        set("title", HIW "冰" HIR "火" HIC "使者");
        set("long", "她是负责护送玩家到中原的秘密使者。\n");
        set("gender", "女性");
        set("age", 20);
        set("max_qi", 99999);
        set("qi", 99999);
        set("max_jingli", 99999);
        set("max_jing", 99999);
        set("max_neili", 99999);
        set("jing", 99999);
        set("jingli", 99999);
        set("neili", 99999);

        set("per", 25);
        set("con", 88);
        set("int", 88);
        set("dex", 88);
        set("str", 88);

        set("inquiry", ([
                "中原" : (: move_bhd :),
        ]));
        set("combat_exp", 10000000);
        set("shen_type", 1);
        setup();
        carry_object("/d/city/npc/cloth/feature")->wear();      
}

int move_bhd()
{
        object me = this_player();

        command("wave");
        command("say 欢迎再回到冰火岛！");

        me->move("/d/quanzhou/yongninggang");
        return 1;
}
