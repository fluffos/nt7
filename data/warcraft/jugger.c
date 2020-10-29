// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("林欣彤[2;37;0m[2;37;0m", ({"juggernaut"}));        
        set("gender", "女性");                
        set("long", "看起来非常的牛B 屁股很大[2;37;0m
它是邓紫棋的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "jugger");
        set("owner_name", "邓紫棋");
        set_temp("owner", "jugger");
        set_temp("owner_name", "邓紫棋");
        ::setup();
}
