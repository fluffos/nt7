// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m混雷啸[2;37;0m[2;37;0m", ({"qinglong"}));        
        set("gender", "男性");                
        set("long", "人中吕布 马中雷啸[2;37;0m
它是史莱姆的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "oxemii");
        set("owner_name", "史莱姆");
        set_temp("owner", "oxemii");
        set_temp("owner_name", "史莱姆");
        ::setup();
}
