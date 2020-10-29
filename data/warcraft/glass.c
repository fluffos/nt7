// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m玻璃[2;37;0m[2;37;0m", ({"vetro"}));        
        set("gender", "男性");                
        set("long", "一块玻璃[2;37;0m
它是净琉璃的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "glass");
        set("owner_name", "净琉璃");
        set_temp("owner", "glass");
        set_temp("owner_name", "净琉璃");
        ::setup();
}
