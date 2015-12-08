#ifndef __PIZZA_HH__
#define __PIZZA_HH__

#include <cstddef>
#include <type_traits>
#include <array>


template<typename... Kinds> struct Pizzeria {

private:

   static constexpr size_t default_slices_count = 8;

   template<typename Kind, typename... Rest> static constexpr bool check_content() {
      return (std::is_same<Kind, Rest>::value || ...);
   }
/*
   template<typename Kind, typename... Rest> static constexpr bool check_duplicates() {
      return (std::is_same(
   }
*/
   template<size_t... Slices> struct Pizza {

   private:
      
      using pizzeria = Pizzeria<Kinds ...>;

   public:

      template<typename Kind> static constexpr size_t count() {
         return ((std::is_same<Kind, Kinds>::value * Slices) + ...);
      }   

      static constexpr std::array<size_t, sizeof... (Slices)> as_array() {
         return std::array<size_t, sizeof... (Slices)> {{Slices ...}};
      }

      using sliced_type = Pizza<(Slices * 2) ...>;

   };

public:

  template<typename Kind> struct make_pizza {
      static_assert(check_content<Kind, Kinds ...>(), "There is no such a pizza name in menu!");
      using type = Pizza<(std::is_same<Kind, Kinds>::value ? default_slices_count : 0) ...>;
   };

};
   

template<typename Pizza1, typename Pizza2> struct best_mix {

};

#endif /* __PIZZA_HH__ */
