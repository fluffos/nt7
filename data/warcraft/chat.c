// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m桃红朱雀[2;37;0m[2;37;0m", ({"chatpet"}));        
        set("gender", "女性");                
        set("long", "一只幼小的桃红朱雀！[2;37;0m
它是聊神的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "chat");
        set("owner_name", "聊神");
        set_temp("owner", "chat");
        set_temp("owner_name", "聊神");
        ::setup();
}
