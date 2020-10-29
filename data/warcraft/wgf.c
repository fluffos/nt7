// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("不死鸟[2;37;0m[2;37;0m", ({"hehe"}));        
        set("gender", "女性");                
        set("long", "这是一只普通的鸟[2;37;0m
它是无言语的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wgf");
        set("owner_name", "无言语");
        set_temp("owner", "wgf");
        set_temp("owner_name", "无言语");
        ::setup();
}
