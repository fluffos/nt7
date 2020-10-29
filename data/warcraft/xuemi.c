// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白虎[2;37;0m[2;37;0m", ({"baihy"}));        
        set("gender", "男性");                
        set("long", "白虎[2;37;0m
它是雪咪咪的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "xuemi");
        set("owner_name", "雪咪咪");
        set_temp("owner", "xuemi");
        set_temp("owner_name", "雪咪咪");
        ::setup();
}
