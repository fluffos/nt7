// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("甲方[2;37;0m[2;37;0m", ({"shuifeng"}));        
        set("gender", "男性");                
        set("long", "甲方[2;37;0m
它是可烦人的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "haishui");
        set("owner_name", "可烦人");
        set_temp("owner", "haishui");
        set_temp("owner_name", "可烦人");
        ::setup();
}
