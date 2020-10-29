// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小香猪[2;37;0m[2;37;0m", ({"xxz"}));        
        set("gender", "男性");                
        set("long", "小香猪[2;37;0m
它是不通帽盔的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "bthead");
        set("owner_name", "不通帽盔");
        set_temp("owner", "bthead");
        set_temp("owner_name", "不通帽盔");
        ::setup();
}
