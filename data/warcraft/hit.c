// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m倚天[2;37;0m[2;37;0m", ({"yitian"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$HIC$倚天[2;37;0m
它是普通百姓的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "hit");
        set("owner_name", "普通百姓");
        set_temp("owner", "hit");
        set_temp("owner_name", "普通百姓");
        ::setup();
}
