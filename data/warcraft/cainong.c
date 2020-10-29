// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("欢狗[2;37;0m[2;37;0m", ({"huangou"}));        
        set("gender", "女性");                
        set("long", "欢狗[2;37;0m
它是花农花的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "cainong");
        set("owner_name", "花农花");
        set_temp("owner", "cainong");
        set_temp("owner_name", "花农花");
        ::setup();
}
