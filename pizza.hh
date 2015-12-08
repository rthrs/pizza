#ifndef __PIZZA_HH__
#define __PIZZA_HH__

#include <type_traits>


template<typename... Kinds> struct Pizzeria {

   template<size_t... Slices> struct Pizza {
      using pizzeria = Pizzeria<Kinds ...>;


   template<typename Kind> static constexpr size_t count() {
      return ((std::is_same(Kind, Kinds)::value * Slices) + ...);
   }


 //  static constexpr std::array<size_t, [N]> as_array() {
      
   };

   /** 
    * nalezy znalezc ktory z kolei to jest typ 'Kind' liscie typow pizy w 
    * pizzeri i dac mu w tym miejscu dla struktury Pizza 8 kawałków 
    */ 
   template<typename Kind> struct make_pizza {
      using type = Pizza<(std::is_same(Kind, Kinds)::value ? default_slices_count : 0>
   };

   


   };
   
   using sliced_type = /*smth*/;

};

template<typename Pizza1, typename Pizza2> struct best_mix {

};

#endif /* __PIZZA_HH__ */