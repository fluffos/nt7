// story:donghai 东海龙传说

#include <ansi.h>

int give_gift(string name);

nosave mixed *story = ({
        "赤脚大仙：斗战胜佛！",
        "孙悟空：哦？你这老头啊？对了，上次托你送的洗髓丹你可送到了？",
        "赤脚大仙：那个自然，自然！小仙怎敢耽误大圣的差使？",
        "孙悟空：噢，那好，那好，我还怕被你给吞没了呢。",
        "赤脚大仙：哪里...哪里...",
        "孙悟空：南极仙翁那老头怎么说？",
        "赤脚大仙：...... 很好，很好... 对了，南极仙翁托小仙告诉大圣您准备赴本届的蟠桃盛会呢！",
        "孙悟空：嗯，看来这礼没有白送。想那蟠桃的滋味老孙我可是很久没有品尝了。",
        "赤脚大仙赔笑道：这只怪那蟠桃熟的太慢，耽误了大圣的口福了。",
        "孙悟空恼道：就是，熟个桃子还磨磨唧唧的，干脆放到锅了煮熟算了！",
        "赤脚大仙一吓，道：这个不可，万万不可。",
        "孙悟空笑道：老孙我随口说说你还当真了？桃子熟了只怕没什么味道。",
        "赤脚大仙抹抹冷汗，道：我口信送到，就不耽误大圣您的工夫了，先走了，蟠桃会上再见！",
        "孙悟空：好，你去吧！",
        "......",
        "孙悟空暗想：现在离那蟠桃盛会还有一段时间，左右无事，何不下凡看看？却不知我那群猴娃们如何了。",
        (: give_gift, "sun" :),
        "听说斗战胜佛孙悟空(sun wukong)凡心思动，来到人间。",
});

string prompt() { return HIM "【神话】" NOR; }

// 每天一次
int interval() { return 24 * 60 * 60; }

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

int give_gift(string name)
{
        object ob;

        ob = new(CLASS_D("misc/") + name);
        if (! objectp(ob))
                return 0;

        NPC_D->place_npc(ob);
        if (! objectp(environment(ob)))
        {
                destruct(ob);
                return 0;
        }

        CHANNEL_D->do_channel(find_object(STORY_D), "sys",
                              ob->name() + "出现在" + environment(ob)->short() +
                              "(" + base_name(environment(ob)) + ")。");
        return 1;
}
