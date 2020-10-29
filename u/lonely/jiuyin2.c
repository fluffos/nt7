#include <ansi.h>

void create()
{
        seteuid(getuid());
}

object book = find_object("/clone/lonely/book/zhenjing2");

object get_owner()
{
        object owner;
        if(objectp(book)) {
                owner = environment(book);
                if(owner->is_character()) return owner;
        }
        return 0;
}

object book_owner = get_owner();
nosave string book_owner_name = objectp(book_owner)?query("name", book_owner):"某人";

string get_book()
{
        if(objectp(book)) destruct(book);
        if(objectp(book_owner) && userp(book_owner)) book_owner->unconcious();
        return book_owner_name + "飞身去抓九阴真经~";
}

int do_rumor(string arg)
{
        CHANNEL_D->do_channel(this_object(), "rumor", arg);
        return 1;
}
nosave mixed *story = ({
        "陈玄风：你这两天怎么不好好练九阴白骨爪了？",
        "梅超风：你还说...你还说...你不爱我了！",
        "梅超风：你不知道，现在流行美甲?人家小姐说我的指甲成色不好,都是白骨爪练的。",
        "陈玄风：......",
        "陈玄风：那...那本真经呢？",
        "梅超风：我想想...哦上次做头发的时候，随便翻翻，忘记拿回来了。",
        "陈玄风口吐白沫，昏了过去。（臭婆娘....败家子....）",
        (: do_rumor, "\"铜尸\" 陈玄风重出江湖..." :),
        book_owner_name + "，悬崖边。",
        book_owner_name + "：逃到这应该找不到我了吧！！抓紧时间练功！",
        book_owner_name + "：恩，九阴真经果然厉害，可惜只有下本.......",
        "陈玄风：哼哼.........",
        book_owner_name + "：哇！鬼呀！！！",
        "陈玄风，" + book_owner_name + "：啊！九阴真经啊！！！！",
        (: get_book :),
        (: do_rumor, book_owner_name + "为了九阴真经不慎跌下悬崖，摔晕了。" :),
});

string prompt() { return HIW "【武林轶事】" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}
