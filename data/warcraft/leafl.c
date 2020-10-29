// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;33m小龙[2;37;0m[2;37;0m", ({"leaflong"}));        
        set("gender", "男性");                
        set("long", "五爪金龙！中国古代龙的群领，是龙族最高的王者，中华图腾！[2;37;0m
它是叶子龙的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "leafl");
        set("owner_name", "叶子龙");
        set_temp("owner", "leafl");
        set_temp("owner_name", "叶子龙");
        ::setup();
}
