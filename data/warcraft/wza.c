// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小怪[2;37;0m[2;37;0m", ({"wzapet"}));        
        set("gender", "男性");                
        set("long", "aaa[2;37;0m
它是无聊人士的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wza");
        set("owner_name", "无聊人士");
        set_temp("owner", "wza");
        set_temp("owner_name", "无聊人士");
        ::setup();
}
