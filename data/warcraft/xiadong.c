// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m冰蚕[2;37;0m[2;37;0m", ({"bingchan"}));        
        set("gender", "女性");                
        set("long", "天空中飞翔的冰蚕。[2;37;0m
它是丁夏冬的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "xiadong");
        set("owner_name", "丁夏冬");
        set_temp("owner", "xiadong");
        set_temp("owner_name", "丁夏冬");
        ::setup();
}
