#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<unistd.h>
#include<math.h>

struct Country {
    char name[30];
    int army_stars;
    int navy_stars;
    int air_force_stars;
    float production;
    int treasury;
    int is_colonized;
};


int coins=100;
float production=1;

void display_rules() {
    printf("\t\t\t\tPREGAME INFO\t\t\t\t\n");
    printf("1) You are the ruler of India and you need to conquer the world by colonizing different countries one by one.\n");
    printf("2) You will have to form an army to colonize different countries, which requires coins.\n");
    printf("3) You will keep getting coins from your country and the countries you have colonized.\n");
    printf("4) To colonize a country, the strength of your army, navy, and air force should each be greater than that of the country you want to colonize.\n");
    printf("5) Once you colonize all the countries, you will be the dictator of the world, and the game will end.\n\n");
    printf("\t\t\tDO YOU WANT TO START THE GAME?\n IF YES PRESS 1\t\t\t\n");
}

int set_cost(int troop){
    int costs[5]={25,100,500,1500,3000};
    return costs[troop];
}

void upgrade(int *army, int *navy, int *air_force) {
    int choice;
    printf("Choose what to upgrade:\n");
    int cost;
    cost=set_cost(*army);
    printf("1) Army Strength, star-%d, cost-%d coins\n",*army,cost);
    cost=set_cost(*navy);
    printf("2) Navy Strength, star-%d, cost-%d coins\n",*navy,cost);
    cost=set_cost(*air_force);
    printf("3) Air Force Strength, star-%d, cost-%d coins\n",*air_force,cost);
    scanf("%d", &choice);


    switch (choice) {
        case 1:
            if (coins >= set_cost(*army)) {
                coins-=set_cost(*army);
                printf("Upgrade successful! Remaining coins: %d\n", coins);
                (*army)++;
            }
            else {
                printf("Not enough coins to upgrade!\n");
            }

            break;
        case 2:
            if (coins >= set_cost(*navy)) {
                coins-=set_cost(*navy);
                printf("Upgrade successful! Remaining coins: %d\n", coins);
                (*navy)++;
            }
            else {
                printf("Not enough coins to upgrade!\n");
            }
            break;
        case 3:
            if (coins >= set_cost(*air_force)) {
                coins-=set_cost(*air_force);
                printf("Upgrade successful! Remaining coins: %d\n", coins);
                (*air_force)++;
            }
            else {
                printf("Not enough coins to upgrade!\n");
            }
            break;
        default: printf("Invalid choice.\n"); return;
    }
    sleep(2);
}

void auto_upgrade(struct Country *country) {
    int choice;
    if(country->army_stars <= country->navy_stars){
        if(country->army_stars <= country->air_force_stars){
            choice=1;
        }
        else choice=3;
    }
    else{
        if(country->navy_stars <= country->air_force_stars){
            choice=2;
        }
        else choice=3;
    }
    switch (choice) {
        case 1:
            if (country->treasury >= 2*set_cost(country->army_stars)) {
                country->treasury-=2*set_cost(country->army_stars);
                printf("%s upgraded its strength!\n", country->name);
                (country->army_stars)++;
            }

            break;
        case 2:
            if (country->treasury >= 2*set_cost(country->navy_stars)) {
                country->treasury-=2*set_cost(country->navy_stars);
                printf("%s upgraded its strength!\n", country->name);
                (country->navy_stars)++;
            }
            break;
        case 3:
            if (country->treasury >= 2*set_cost(country->army_stars)) {
                country->treasury-=2*set_cost(country->army_stars);
                printf("%s upgraded its strength!\n", country->name);
                (country->air_force_stars)++;
            }
            break;
        default: printf("Error\n"); return;
    }
}

void colonize(struct Country *country, int *army, int *navy, int *air_force,int *colonized) {
    if (country->is_colonized) {
        printf("%s is already colonized.\n", country->name);
        return;
    }

    if (*army >= country->army_stars && *navy >= country->navy_stars && *air_force >= country->air_force_stars) {
        country->is_colonized = 1;
        coins += 10; // Reward for colonization
        printf("You have successfully colonized %s! Coins: %d\n", country->name, coins);
        *army-= country->army_stars;
        *navy-= country->navy_stars;
        *air_force-= country->air_force_stars;
        (*colonized)++;
    }
    else {
        printf("Your forces are not strong enough to colonize %s.\n", country->name);
    }
    sleep(3);
}

int main(){
    int army_stars=0;
    int navy_stars=0;
    int air_force_stars=0;
    int colonized=0;
    int start;
    display_rules();

    scanf("%d", &start);
    if (start != 1) {
        printf("Exiting the game.\n");
        return 0;
    }

    struct Country countries[] = {

        {
            "Canada",3,1,1,0.5,0,0
        },
        {
            "Zimbabwe",1,0,1,0.2,0,0
        },
          {
            "South Africa",3,2,3,0.8,0,0
        },
          {
             "Egypt",1,0,1,0.2,0,0
        },
          {
            "Morocco",2,0,0,0.2,0,0
        },
          {
            "Democratic Republic Of Congo",1,1,1,0.3,0,0
        },
          {
            "Portugal",1,0,1,0.2,0,0
        },
          {
            "Spain",2,1,2,0.5,0,0
        },
          {
            "France",3,1,2,0.6,0,0
        },
          {
            "United Kingdom",4,4,4,1.2,0,0
        },
          {
            "Ireland",2,1,1,0.4,0,0
        },
          {
            "Italy",1,2,1,0.4,0,0
        },
          {
            "Israel",0,1,1,0.2,0,0
        },
          {
            "Jordan",1,2,1,0.4,0,0
        },
          {
            "Belgium",1,0,0,0.1,0,0
        },
          {
            "Netherlands",2,3,3,0.8,0,0
        },
          {
            "Germany",2,2,3,0.7,0,0
        },
          {
            "Switzerland",2,3,2,0.7,0,0
        },
          {
            "Austria",1,1,0,0.3,0,0
        },
          {
           "Hungary",2,1,2,0.5,0,0
        },
          {
            "Romania",3,1,1,0.6,0
        },
          {
             "Poland",0,0,1,0.2,0,0
        },
          {
            "Denmark",4,3,2,1,0,0
        },
          {
            "Norway",2,3,4,0.9,0,0
        },
          {
            "Sweden",3,1,2,0.6,0,0
        },
          {
            "Finland",3,1,2,0.7,0,0
        },
          {
           "Ukraine",2,4,3,0.9,0,0
        },
          {
            "Turkey",0,1,1,0.2,0,0
        },
          {
            "Armenia",2,2,2,0.6,0,0
        },
          {
            "Azerbaijan",3,0,0,0.4,0,0
        },
          {
            "Iraq",3,2,1,0.7,0,0
        },
          {
            "Saudi Arabia",3,1,1,0.7,0,0
        },
          {
            "United Arab Emirates",3,1,1,0.6,0,0
        },
          {
            "Iran",3,2,2,0.8,0,0
        },
          {
            "Pakistan",4,2,3,0.9,0,0
        },
          {
            "China",4,4,4,1.2,0,0
        },
        {
            "Srilanka",2,2,3,0.7,0,0
        },
        {
            "Bangladesh",1,1,1,0.3,0,0
        },
        {
            "Australia",0,1,0,0.2,0,0
        },
        {
            "Russia",4,4,4,1.2,0,0
        },
        {
            "Dominican Republic",3,2,1,0.7,0,0
        },
        {
            "Colombia",3,2,1,0.8,0,0
        },
        {
            "Chile",4,2,3,1.5,0,0
        },
        {
           "Argentina",3,0,0,0.4,0,0
        },
        {
            "Brazil",3,2,1,0.75,0,0
        },
        {
            "Mexico",3,2,1,0.75,0,0
        },
        {
            "United States Of America",4,4,4,1.2,0,0
        },
        {
            "Singapore",2,2,1,0.5,0,0
        },
        {
            "New Zealand",2,1,1,0.5,0,0
        },
        {
            "Malaysia",0,0,0,0.2,0,0
        },
    }
        ;
    int num_countries = sizeof(countries) / sizeof(countries[0]);

    time_t start_time=time(NULL);
    while (1) {
        printf("===================================\n");
        printf("COINS: %d\n", coins);
        printf("Army: %d | Navy: %d | Air Force: %d\n", army_stars, navy_stars, air_force_stars);
        printf("===================================\n\n");

        printf("1) Upgrade Strength\n");
        printf("2) Attempt Colonization\n");
        printf("3) Refresh\n");
        printf("4) Exit Game\n\n");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                upgrade(&army_stars, &navy_stars, &air_force_stars);
                break;
            case 2: {
                printf("Choose a country to colonize:\n");
                for (int i = 0; i < num_countries; i++) {
                    if (!countries[i].is_colonized) {
                        printf("\n%d) %s (Army: %d, Navy: %d, Air Force: %d)\n", i + 1, countries[i].name, countries[i].army_stars, countries[i].navy_stars, countries[i].air_force_stars);
                    }
                }
                int country_choice;
                scanf("%d", &country_choice);

                if (country_choice >= 1 && country_choice <= num_countries) {
                    colonize(&countries[country_choice - 1], &army_stars, &navy_stars, &air_force_stars,&colonized);
                }
                else {
                    printf("Invalid choice.\n");
                }
                break;
            }
            case 3:
                break;
            case 4:
                printf("Exiting game. See you next time!\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }

        system("cls");
        if(time(NULL)-start_time>1){
            coins=coins+floor(time(NULL)-start_time)*production;
            int colonized_money=0;
            for(int i=0; i<num_countries;i++){
                if(countries[i].is_colonized){
                    colonized_money+=floor(time(NULL)-start_time)*countries[i].production;
                }
                else{
                    countries[i].treasury+=floor(time(NULL)-start_time)*countries[i].production;
                }
            }
            printf("All colonized countries gave %d coins\n",colonized_money);
            coins+=colonized_money;
            start_time=time(NULL);
        }

        for(int i=0;i<num_countries;i++){
            if(!countries[i].is_colonized){
                auto_upgrade(&countries[i]);
            }
        }

        printf("Countries colonized: %d\n", colonized);
        if(colonized>49){
                printf("Congratulations, you are the dictator of the world!!!");
            return 0;
        }
    }
}
