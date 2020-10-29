// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;32m奔驰[2;37;0m[2;37;0m", ({"benz"}));        
        set("gender", "男性");                
        set("long", "this is benz[2;37;0m
它是鹿鹿的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "juliet");
        set("owner_name", "鹿鹿");
        set_temp("owner", "juliet");
        set_temp("owner_name", "鹿鹿");
        ::setup();
}
