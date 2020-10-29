// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小香猪[2;37;0m[2;37;0m", ({"xxz"}));        
        set("gender", "男性");                
        set("long", "小香猪[2;37;0m
它是不通神棍的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "btclub");
        set("owner_name", "不通神棍");
        set_temp("owner", "btclub");
        set_temp("owner_name", "不通神棍");
        ::setup();
}
