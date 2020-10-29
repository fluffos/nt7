// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("巴拿马[2;37;0m[2;37;0m", ({"aobama"}));        
        set("gender", "男性");                
        set("long", "finish[2;37;0m
它是医生的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "doctor");
        set("owner_name", "医生");
        set_temp("owner", "doctor");
        set_temp("owner_name", "医生");
        ::setup();
}
