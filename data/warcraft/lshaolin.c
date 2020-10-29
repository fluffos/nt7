// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m丰韵美人[2;37;0m[2;37;0m", ({"meimei"}));        
        set("gender", "女性");                
        set("long", "很骚包的美女[2;37;0m
它是渡美妞的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lshaolin");
        set("owner_name", "渡美妞");
        set_temp("owner", "lshaolin");
        set_temp("owner_name", "渡美妞");
        ::setup();
}
