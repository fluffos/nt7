// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("法拉利[2;37;0m[2;37;0m", ({"falali"}));        
        set("gender", "男性");                
        set("long", "这是法拉利的进口车厂法拉利于2014年推出的一款跑车Ferrari F150[2;37;0m
它是爱尚汽车的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "loewe");
        set("owner_name", "爱尚汽车");
        set_temp("owner", "loewe");
        set_temp("owner_name", "爱尚汽车");
        ::setup();
}
