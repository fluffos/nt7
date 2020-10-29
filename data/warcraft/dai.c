// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m朱雀[2;37;0m[2;37;0m", ({"vermilion"}));        
        set("gender", "女性");                
        set("long", "上古四大神兽之一。她是一种红色的鸟，其身覆盖火焰，终日不灭。[2;37;0m
它是小呆的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dai");
        set("owner_name", "小呆");
        set_temp("owner", "dai");
        set_temp("owner_name", "小呆");
        ::setup();
}
