// story:beihai 北海传说

#include <ansi.h>

int give_gift(string name);

nosave mixed *story = ({
        "华山。",
        "李铁嘴打了个哈欠，百无聊赖。",
        "一人忽然闯了进来，看看李铁嘴，忽然道：你的卦可准？",
        "李铁嘴眼睛瞪得大大的，道：不准不要钱。",
        "来人哈哈大笑道：好！好！那么你算算，明天下不下雨？",
        "李铁嘴摆好卦签，一顿乱算。",
        "来人冷冷的看着。",
        "李铁嘴道：明天午时应该下雨，一寸三分！",
        "来人道：倘然不对，那又如何？",
        "李铁嘴白眼一翻，道：哈！那你就来取我性命好了！",
        "来人冷笑一声，转身即走。",
        "李铁嘴默默不作言语，收拾行囊，从后门溜走了。",
        "......",
        "北海龙宫。",
        "老龙王静坐，心里暗道：眼看午时就要过，这卦不就错了？我不下雨，天上能出云彩？",
        "忽然天宫旨意到：张天师求雨，玉帝已准。午时华山降雨一寸三分！",
        "啊？老龙王翻翻白眼，吐了口白沫，倒在地上。",
        "半天过后，龙王爬起，心中忿忿：岂有此理？慢来，我就降它一寸四分雨，不还是我赢？",
        "......",
        "龙王降过雨，赶到李铁嘴处要人头：人呢？人呢？跑了！！！",
        "......",
        "玉帝大怒：好么，和我作对！",
        (: give_gift, "beihai" :),
        "听说北海龙王(king of dragon)降雨失责，被贬谪至凡间。",
});

string prompt() { return HIM "【神话】" NOR; }

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
