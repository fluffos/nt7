// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m兵[1;32m虎[2;37;0m[2;37;0m", ({"binghu"}));        
        set("gender", "女性");                
        set("long", "老虎[2;37;0m
它是兵丙的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "bingbing");
        set("owner_name", "兵丙");
        set_temp("owner", "bingbing");
        set_temp("owner_name", "兵丙");
        ::setup();
}
