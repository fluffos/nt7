#include <ansi.h>

inherit NPC;

int move_bhd();
int join_battle();

void create()
{
        set_name(HIM "谢晓诗" NOR, ({ "xiexiao shi", "xiexiao", "shi" }));
        set("title", HIW "冰" HIR "火" HIC "使者");
        set("long", "她是负责护送玩家到冰火岛的秘密使者。\n");
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
                "冰火岛" : (: move_bhd :),
                "帮派争夺战" : (: join_battle :),
        ]));
        set("combat_exp", 10000000);
        set("shen_type", 1);
        setup();
        carry_object("/d/city/npc/cloth/feature")->wear();      
}

int move_bhd()
{
        object me = this_player();
        
        // 身上钱不足
        if( query("balance", me)<100 )
        {
                command("say 你的银库中似乎缺钱吧，我护送你到冰火岛至少得一百两黄金！");
                return 1;
        }
        addn("balance", -100, me);
        
        command("say 既然如此，我就护送你到冰火岛吧！");

        me->move("/maze/binghuodao/haitan"); 
        return 1;
}

int join_battle()
{
        object me = this_player();
        BUNCH_D->join_battle(me);
        return 1;
}

