#ifndef __PIZZA_HH__
#define __PIZZA_HH__

#include <cstddef>
#include <type_traits>
#include <array>

template<typename... Kinds> struct Pizzeria {

private:

   static constexpr size_t default_slices_count = 8;

   template<typename Kind, typename... Menu> static constexpr size_t count_kind() {
      return (std::is_same<Kind, Menu>::value + ...);
   }
 
   static constexpr bool check_duplicates() {
      return ((count_kind<Kinds, Kinds ...>() == 1) && ...);
   }

   template<size_t... Slices> struct Pizza {
        
      using pizzeria = Pizzeria<Kinds ...>;

      template <typename Type> static constexpr size_t maxi_pizza(size_t slices) {
         static_assert(Type::yumminess(0) == 0, "Yumminess not equals 0 for 0 slices!"); 
         decltype(Type::yumminess(slices)) total = 0;
         size_t size = 0;		
         for(size_t i = 0; i <= slices; i++) {
            auto acc = Type::yumminess(i);
            if(acc > total) {
               total = acc;
               size = i;
            }
         }
         return size;
      }  
      
      template<typename Second> struct mix {
         using mixed = Pizza<maxi_pizza<Kinds>(Slices + Second::template count<Kinds>()) ...>;
      };


      template<typename Kind> static constexpr size_t count() {
         return ((std::is_same<Kind, Kinds>::value ? Slices : 0) + ...);
      }   

      static constexpr std::array<size_t, sizeof... (Slices)> as_array() {
         return std::array<size_t, sizeof... (Slices)> {{Slices ...}};
      }

      using sliced_type = Pizza<(Slices * 2) ...>;

   };

public:

   static_assert(check_duplicates(), "Duplicated pizzas!");
   
   template<typename Kind> struct make_pizza {
      static_assert(count_kind<Kind, Kinds ...>() == 1, "There is no such a pizza in menu!");
      using type = Pizza<(std::is_same<Kind, Kinds>::value ? default_slices_count : 0) ...>;
   };

};

template<typename Pizza1, typename Pizza2> struct best_mix {
   static_assert(std::is_same<typename Pizza1::pizzeria, typename Pizza2::pizzeria>::value, "Tried to mix from distinct pizzeria!");
	using type = typename Pizza1::template mix<Pizza2>::mixed;
};

#endif /* __PIZZA_HH__ */
