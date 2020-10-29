mapping area = ([
         "扬州城" : ({
                 "/d/city/","beidajie1","beidajie2","beimen","bingyin",
                "kedian2","lichunyuan","meigui","nandajie1","nandajie2",
                      "nanmen","neizhai","mudan","qianzhuang","shuyuan","xidajie1",
                      "xidajie2","ximen","xiting","xixiang","yamen","ymzhengting",
                      "zahuopu","zhengting","zuixianlou","zuixianlou2"
                         }),
"北京城" : ({"/d/beijing/","alley1","alley2","alley3","anding","aobai1",
            "aobai10","aobai11","aobai12","aobai2","aobai3","aobai4",
            "aobai5","aobai6","aobai7","aobai8","aobai9","bingqiku",
            "bingyin1","bingyin2","bridge","bridge2","bridge3","ceting",
            "chaguan","chaoyan1","chaoyan2","chaoyang","dangpu","datiepu",
            "dating","di_an1","di_an2","di_an3","di_an4","di_anmen",
            "dongcha1","dongcha2","dongchangdamen","dongmen","duchang",
            "duchang2","fotang","guancai2","haigang","hbridge","huayuan",
            "huichunt","jiulou1","jiulou2","kang1","kang2","kang3",
            "mianguan","nandaj1","nandaj2","qianzhua","road1","road10",
            "road2","road3","road4","road5","road6","road7","road8",
            "road9","tian_anm","tuzai","wangfu1","wangfu2","wangfu3",
            "xichang1","xichang2","xichangdamen","xidan","xidan1",
            "ximen","ximenwai","xisi","xisi2","yihongyu","yongding",
            "zahuopu","zhengmen"
            }),
        "白驼山" : ({
                "/d/baituo/","barn","base1","base2","bthill","btroad",
                     "changlang1","changlang2","changlang3","changlang4","dating",
                  "lingshege","road1","road2","road3","road4","road5","shegu1",
                   "shegu10","shegu11","shegu12","shegu13","shegu14","shegu15","shegu16",
                  "shegu17","shegu18","shegu19","shegu20","shegu21","shegu22","shegu23",
                  "shegu24","shegu25","shegu26","shegu27","shegu28","shegu29","shegu30",
                  "shegu2","shegu3","shegu4","shegu5","shegu6","shegu7","shegu8","shegu9",
                  "shegu_maze10","shegu_maze2","shegu_maze1","shegu_maze3","shegu_maze4",
                  "shegu_maze5","shegu_maze6","shegu_maze7","shegu_maze8","shegu_maze9",
                    "shegu_pool","shegu_shanya",
                    }),
         "灵鹫宫" : ({
                 "/d/lingjiu/","biguan","changl1","changl10","changl11",
                    "changl12","changl13","changl14","changl15","changl2",
                    "changl3","changl4","changl5","changl6","changl7","changl8",
                      "changl9","daban","dadao1","dadao2","damen",
                    "dating","huayuan","jian","liangong","men1","men2","men3",
                      "shanjiao","shufang","xiaodao2","xianchou","xiaodao1",
                     }),
           "泉州城" : ({
                   "/d/quanzhou/","alabo","anhai","anqibu",
                      "bangbu","cangjing","caoan1","caoan2","chengtian","chmiao",
                "chuanwu","caoan1","chxiang","cien","citong_e1",
                      "daobu","datiepu","dongta","dufu","duxiang","dxbaodian",
                      "dxxiang","enyuan","fengdong","gangkou1","gangkou2","gangkou3",
                      "gangkou4","ganlu","gtxiang","gushao","hjting","houshan",
                      "houyuan","houzhu","huru","jianbu","jiangfu","jiangfu1",
                      "jiedao1","jiedao2","jishi","kaiyuan","kaojiao","laojun",
                "laozhai","liandan","liang","liangcang",
                      "lingmu","luanshi","lyqiao","mituo","mixiang","nantai",
                      "neitang","qianshou","qianting","qingjing","qingyuan","qzkedian",
                "qzkedian2","qzroad5","ruixiang","shanlu1","shanlu10",
                      "shanlu2","shanlu3","shanlu4","shanlu5","shanlu6","shijiefu",
                      "ship","shisun","shuiguan","silkshop","sjqiao","taoci",
                      "taoran","tianwang","tiaoyu","tudi","tumen","wangzhou",
                      "weiyuan","well","well1","wgdamen","wglou1","wglou2",
                       "xinmen","xiqiao","xita","xiyuan",
                      "xmqiao","xuetang","yaofang","yaopu","yongning","yuanhe",
                      "yuetai","zahuopu","zhongxin","zoulang1","zoulang2",
                    }),
]);

string *city = ({"扬州城", "北京城", "白驼山", "灵鹫宫", "泉州城"});

int place_room(object me, object ob)
{
          string *location, site_file, site_name;
          int size;

          site_name = city[random(sizeof(city))];
          location = area[site_name];
          size = sizeof(location);

          site_file = location[0] + location[random(size - 1) + 1];
          set("area", site_name, ob);
          set("place_name", site_file, ob);
          set("killer",query("id",  me), ob);
          ob->move(site_file);

          return 1;
}