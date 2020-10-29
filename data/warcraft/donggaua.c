// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("血之盟约[2;37;0m[2;37;0m", ({"sleeppbag"}));        
        set("gender", "男性");                
        set("long", "于一身的强大生物，幻兽呀！请你以最深的灵性，聆听我的倾诉[2;37;0m
它是地面亲爹的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "donggaua");
        set("owner_name", "地面亲爹");
        set_temp("owner", "donggaua");
        set_temp("owner_name", "地面亲爹");
        ::setup();
}
