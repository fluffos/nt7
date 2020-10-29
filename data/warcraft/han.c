// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火凤[2;37;0m[2;37;0m", ({"zhuque"}));        
        set("gender", "女性");                
        set("long", "朱雀[2;37;0m
它是漫无目的的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "han");
        set("owner_name", "漫无目的");
        set_temp("owner", "han");
        set_temp("owner_name", "漫无目的");
        ::setup();
}
