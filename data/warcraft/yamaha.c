// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("中华田园犬[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "中华田园犬[2;37;0m
它是雅马哈的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yamaha");
        set("owner_name", "雅马哈");
        set_temp("owner", "yamaha");
        set_temp("owner_name", "雅马哈");
        ::setup();
}
