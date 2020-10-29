// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;34m蓝凤[2;37;0m[2;37;0m", ({"myshou"}));        
        set("gender", "女性");                
        set("long", "四大神兽[2;37;0m
它是蓝色妖姬的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "kingoy");
        set("owner_name", "蓝色妖姬");
        set_temp("owner", "kingoy");
        set_temp("owner_name", "蓝色妖姬");
        ::setup();
}
