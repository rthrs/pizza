/*============================================================================*/
/*                    JNP Grupa 7 - Zadanie 4 - Pizza                         */
/*                      Artur Myszkowski - am347189                           */
/*                        Emil Hotkowski - eh359530                           */
/*============================================================================*/

#ifndef __PIZZA_HH__
#define __PIZZA_HH__

#include <cstddef>
#include <type_traits>
#include <array>

#define ASSERT_YUMMINESS  "Yumminess is not equal 0 for 0 slices!"  
#define ASSERT_DUPLICATES "Duplicated pizzas!"
#define ASSERT_NO_PIZZA   "There is no such pizza in menu!" 
#define ASSERT_DISTINCT   "Tried to mix from distinct pizzeria!"

/**
 * Typ szablonowy reprezentujący pizzerię. 
 */
template<typename... Kinds> 
struct Pizzeria {

private:

   static constexpr std::size_t default_slices_count = 8;
 
   /**
    * Zliczenie ilości wystąpień rodzaju 'Kind' w menu pizzerii.
    */  
   template<typename Kind, typename... Menu> 
   static constexpr std::size_t count_kind() {
      return (std::is_same<Kind, Menu>::value + ...);
   }
      
   /**
    * Sprawdzenie czy poszczególnie rodzaje pizzy podane 
    * przy definicji pizzerii występują dokładnie raz. 
    */ 
   static constexpr bool check_duplicates() {
      return ((count_kind<Kinds, Kinds ...>() == 1) && ...);
   }
   
   /**
    * Struktra reprezentująca pizzę. 
    */
   template<std::size_t... Slices> 
   struct Pizza {
      
      // Definicja pizzerii, z której pochodzi pizza. 
      using pizzeria = Pizzeria<Kinds ...>;
      
      /**
       * Oblicza optymalną w sensie smakowitości ilość kawałków 
       * rodzaju 'Type' dla zmiksowanej pizzy. 'slices' to ilość 
       * dostępnych kawałków rodzaju 'Type'.
       */
      template <typename Type> 
      static constexpr std::size_t maxi_pizza(size_t slices) {
         static_assert(Type::yumminess(0) == 0, ASSERT_YUMMINESS);
         decltype(Type::yumminess(slices)) total = 0;
         std::size_t size = 0;		
         for(std::size_t i = 0; i <= slices; i++) {
            auto acc = Type::yumminess(i);
            if(acc > total) {
               total = acc;
               size = i;
            }
         }
         return size;
      }  
      
      /**
       * Struktura udostępniająca definicję 'mixed', oznaczającą najlepszą 
       * możliwą pizzę uzyskaną poprzez zmiksowanie siebie z pizzą 'Second'.
       */
      template<typename Second> 
      struct mix {
         using mixed = Pizza<maxi_pizza<Kinds>
                             (Slices + Second::template count<Kinds>()) ...>;
      };

      /**
       * Zwraca ilość kawałków pizzy typu 'Kind'.
       */
      template<typename Kind> 
      static constexpr std::size_t count() {
         return ((std::is_same<Kind, Kinds>::value ? Slices : 0) + ...);
      }   
      
      /**
       * Zwraca tablicę reprezentującą ilości poszczególnych rodzajów, z których
       * składa się pizza (zgodnie z kolejnością rodzajów podanych przy 
       * definiowaniu pizzerii).
       */
      static constexpr std::array<std::size_t, sizeof... (Slices)> as_array() {
         return std::array<std::size_t, sizeof... (Slices)> {{Slices ...}};
      }
      
      // Definicja pizzy podzielonej na dwa razy więcej kawałków.
      using sliced_type = Pizza<(Slices * 2) ...>;

   };

public:

   static_assert(check_duplicates(), ASSERT_DUPLICATES);

   /**
    * Struktura, której definicja 'type' reprezentuje 
    * 8-kawałkową pizzę rodzaju 'Kind'.
    */
   template<typename Kind> 
   struct make_pizza {
      static_assert(count_kind<Kind, Kinds ...>() == 1, ASSERT_NO_PIZZA);
      using type = Pizza<(std::is_same
                          <Kind, Kinds>::value ? default_slices_count : 0) ...>;
   };

};

/**
 * Struktura, której publiczna definicja 'type' określa najlepszą możliwą pizzę,
 * jaką można złożyć z podanych pizz 'Pizza1' oraz 'Pizza2'. 
 */
template<typename Pizza1, typename Pizza2>
struct best_mix {
   static_assert(std::is_same
                 <typename Pizza1::pizzeria, typename Pizza2::pizzeria>::value, 
                 ASSERT_DISTINCT);
	using type = typename Pizza1::template mix<Pizza2>::mixed;
};

#endif /* __PIZZA_HH__ */
