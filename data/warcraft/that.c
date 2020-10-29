// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("蛋蛋[2;37;0m[2;37;0m", ({"dand"}));        
        set("gender", "女性");                
        set("long", "蛋[2;37;0m
它是那个的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "that");
        set("owner_name", "那个");
        set_temp("owner", "that");
        set_temp("owner_name", "那个");
        ::setup();
}
