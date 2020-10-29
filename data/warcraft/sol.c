// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[41;1m[1;37m如果[47;1m[1;37m痛[2;37;0m[2;37;0m", ({"loveky"}));        
        set("gender", "男性");                
        set("long", "$HBRED$$HIW$如果$HBWHT$$HIW$痛[2;37;0m
它是菲拉洛的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "sol");
        set("owner_name", "菲拉洛");
        set_temp("owner", "sol");
        set_temp("owner_name", "菲拉洛");
        ::setup();
}
