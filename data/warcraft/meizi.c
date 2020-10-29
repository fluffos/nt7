// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m倚天[2;37;0m[2;37;0m", ({"xmeizi"}));        
        set("gender", "女性");                
        set("long", "$BLINK$$HIC$倚天[2;37;0m
它是妹子的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "meizi");
        set("owner_name", "妹子");
        set_temp("owner", "meizi");
        set_temp("owner_name", "妹子");
        ::setup();
}
