//Cracked by Kafei
// /d/huanghe/npc/guanjia.h
// by aln 2 / 98
#include <changle.h>
#include <ansi.h>
#include D_STORE
#include D_BIAO
#include D_GUEST
#include D_BUSINESS
//#include BANGS + "REGIONS.h"
int is_victim(object, string);


string ask_job()
{
        object me = this_player(), leader, ling, ob, *obj, dest, room;
        string myfam, *files, file, region, biaoju, ob_bang;
        int i, temp, myexp;
        mapping job;

        string *levels = ({
                "3000",
                "5000",
               "10000",
               "20000",
               "50000",
              "100000",
              "300000",
              "500000",
        });

        myfam = (string)query("party/party_name");
//        if( (string)me->query_temp("bangs/fam") != myfam )
        if( query("party/party_name", me) != myfam )
                return RANK_D->query_rude(me) + "莫非是想打听我帮的秘密吧。";  

        if( time()<query("bangs/asktime", me)+60 )
                return RANK_D->query_rude(me) + "不是刚问过我吗？";

        if( objectp(leader = me->query_leader()) ) {
                if( leader != this_object() )
                         return RANK_D->query_rude(me) + "！入了帮还三心二意跟别人？！";
        }

        set("bangs/asktime", time(), me);

        if( !(ling = present("bang ling", me)) ) {
                ling = new(BANGLING);
                set("owner",query("id",  me), ling);
                set("fam", myfam, ling);
                set("combat_exp", query("combat_exp"), ling);
                ling->move(me);
                message_vision("$N把一"+query("unit", ling)+ling->name()+"扔给$n。\n",this_object(),me);
        }

        myexp=query("combat_exp", me);
        myexp = (4 * myexp + random(2 * myexp)) / 5;

        temp = sizeof(levels);
        for( i = 0; i < temp; i++ ) 
                if( myexp < atoi(levels[i]) ) break;

        if( i >= temp )
                return "最近没有适合你的帮务。";

        job = (BANGJOB + levels[i])->query_job();

        if( mapp(query("job", ling)) )
                delete("job", ling);
        set("job", job, ling);

        if( ob = present("caili", me) )
                destruct(ob);

        switch(job["type"]) {
        case "寻":
                command("nod");
                set("job/max", atoi(levels[i]), ling);
                return "你去把" + job["name"] + "找来。";
                break;

        case "杀":
                command("nod");
                set("job/max", atoi(levels[i]), ling);
                return "你去把" + job["area"] + "的" + job["name"] + "杀了。";
                break;

        case "摊费":
                command("nod");
                job = info_store[random(sizeof(info_store))];
                set("job/name", job["name"], ling);
                set("job/boss", job["boss"], ling);
                set("job/place", job["place"], ling);
                return  job["name"] + "这个月还没有交摊费，快去要来！";
                break;

        case "截镖":
                obj = filter_array(children(BIAOTOU), (: clonep :));
                if( sizeof(obj) < 10 ) {
                        ob = new(BIAOTOU);
                        file = biao_places[random(sizeof(biao_places))];
                        ob->move(file);
                        dest = environment(ob);            
                        message("vision",
                        ob->name() + "押着镖车走了过来。\n",
                        dest, ({ob}));
                        region = explode(file, "/")[1];
                        set("job/name",query("nickname",  ob), ling);
                        return "去踩盘的弟兄们回来讲，" + 
                        query("nickname", ob)+
                        "的镖车将经过" + 
                        //region_names[region] +
                        to_chinese("region") +
                        query("short", dest)+"。";
                } else {
                        ob = obj[random(sizeof(obj))];
                        dest = environment(ob);
                        biaoju=query("nickname", ob);

                        if( !dest || !biaoju ) {
                                destruct(ob);
                                command("shake");
                                return "你歇着吧，最近没有要紧的帮务。";
                        }

                        file = base_name(dest);
                        if( strsrch(file, "/d/") != 0
                         || !mapp(query("exits", dest))){
                                destruct(ob);
                                command("shake");
                                return "你歇着吧，最近没有要紧的帮务。";
                        }

                        command("nod");
                        region = explode(file, "/")[1];
                        set("job/name", biaoju, ling);
                        return "去踩盘的弟兄们回来讲，" + biaoju + 
                        "的镖车将经过" + 
                        //region_names[region] + 
                        to_chinese("region") +
                        query("short", dest)+"。";
                }
                break;

        case "示威":
                obj = filter_array(children(BANGZHONG), (: clonep :));
                if( sizeof(obj) ) {
                obj = filter_array(obj, "is_victim", this_object(), myfam);
                if( sizeof(obj) ) {
                        command("nod");
                        ob = obj[random(sizeof(obj))];
                        ob_bang=query("title", ob);
                        set_temp("bangs/victim", ob_bang, me);
                        set("job/name", ob_bang, ling);
                        return "最近" + ob_bang + "经常跟我们过不去，你去杀一个示示威！";
                }
                }
                break;

        case "送礼":
                command("nod");

                job = info_guest[random(sizeof(info_guest))];
                region = explode(job["file"], "/")[1];

                ob = new(CAILI);
                set("job", job, ob);
                set("owner", me, ob);
                set("job/title", job["title"], ling);
                set("job/area", job["area"], ling);
                ob->set("long",
"这是一份" + myfam + "帮主送给" + "「" + job["title"] + "」" + "的彩礼。\n");
                ob->move(me);
                message_vision("$N将一"+query("unit", ob)+ob->name()+"交给$n。\n",this_object(),me);
                return "你把这份彩礼送给" + job["area"] + "的" + "「" + job["title"] + "」" + "。";
                break;

        case "买卖":
                command("nod");
                files = get_dir(BANGGOOD);
                if( !sizeof(files) ) {
                         command("shake");
                         return "你歇着吧，最近没有要紧的帮务。";
                }
                file = BANGGOOD + files[random(sizeof(files))];
                ob = new(file);
                ob->move(me);
                message_vision("$N将一"+query("unit", ob)+ob->name()+"交给$n。\n",this_object(),me);
                set("job/name", ob->name(), ling);
                set("job/good",query("id",  ob), ling);
                set("job/prices", info_business[ob->name()], ling);
                return "你把这"+query("unit", ob)+ob->name()+"拿去卖个好价钱。";
                break;

        case "伙计":
                command("nod");
                set("job/name", "伙计", ling);
                return "你去天宝阁当差吧。";
                break;
        }

        command("shake");
        return "你歇着吧，最近没有要紧的帮务。";
}

void do_start(object me, object ob)
{
        ob->move(environment());
        destruct(this_object());
}

int accept_object(object who, object ob)
{
        object obj;
        int bonus, record;
        string name, chname = "";
        mapping job;

        if( query("party/party_name", who) != query("party/party_name") )
                return notify_fail(name() + "大怒道：大胆！想谋害本总管！！！\n");

        if( !(obj = present("bang ling", who)) )
                return notify_fail(name() + "大怒道：没有用的东西，连帮令都会搞丢？！\n");

        if( !mapp(job=query("job", obj)) )
                return notify_fail(name() + "大怒道：没有用的东西，连自己的帮务都记不住？！\n");

        switch(job["type"]) {
        case "寻":
                name = ob->name();
                for(int i = 0; i < strlen(name); i++)
                        if(name[i] > 160 && name[i] < 255) 
                                chname += name[i..i];
                if( chname != job["name"] )
                        return notify_fail(name() + "大怒道：没有用的东西，连自己的帮务都记不住？！\n");
                bonus=job["bonus"]*job["max"]/(query("combat_exp", who)+1000);
                record = bonus / 2 + random(bonus);
                log_file("test/BangJob",sprintf("%s于%s时找到%s得%s经验点\n",query("name", who),ctime(time()),chname,chinese_number(record)));
                bonus = job["score"];
                break;

        case "截镖":
                if( base_name(ob) != BIAOHUO )
                        return notify_fail(name() + "大怒道：没有用的东西，连一枝镖都搞不定！\n");
                if( query("my_killer", ob) != query("id", who) )
                        return notify_fail(name() + "大怒道：江湖中最讲究的就是信用，再欺世盗名就宰了你！\n");
                break;  
        }

        command("nod");
        delete("job", obj);

        addn("combat_exp", record, who);
        addn("shen", -bonus, who);
        addn("score", bonus, obj);

        remove_call_out("store");
        call_out("store", 1, ob);
        return 1;
}

void store(object ob)
{
 //       ob->move("/d/shenlong/cangku");
  destruct(ob);
}

private is_victim(object ob, string arg)
{
        string fam;

        if( !stringp(fam=query("title", ob)))return 0;
        if( fam == arg ) return 0;

        return 1;
}
