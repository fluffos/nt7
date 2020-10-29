// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m天长[1;32m地久[2;37;0m[2;37;0m", ({"forever"}));        
        set("gender", "男性");                
        set("long", "如果你是我的传说 让他天长地久 追梦的人 为你在等候 [2;37;0m
它是浪漫传说的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "romance");
        set("owner_name", "浪漫传说");
        set_temp("owner", "romance");
        set_temp("owner_name", "浪漫传说");
        ::setup();
}
